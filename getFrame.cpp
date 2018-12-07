/******************************************************************************
 *
 * McamGetTimeCodes.cpp
 * Author: Bryan D. Maione
 *
 * This script is a usefull diagnostic that collects timecodes from all the Mcams
 * in an array and saves them to a file.
 *
 *****************************************************************************/
 // gcc -std=c++11 -o  McamGetTimeCodes McamGetTimeCodes.cpp -lMantisAPI -lpthread -lm -lstdc++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "mantis/MantisAPI.h"
#include <string>
#include <vector>
#include <mutex>

using namespace std;
vector<FILE*> vOutFiles;

mutex mutexM;

void newMCamCallback(MICRO_CAMERA mcam, void* data)
{
    static int mcamCounter = 0;
    MICRO_CAMERA* mcamList = (MICRO_CAMERA*) data;
    lock_guard<mutex> guard(mutexM);
    mcamList[mcamCounter++] = mcam;
}


inline int getOutFileID(int camId){
	char temp[10];
	sprintf(temp, "%d", camId);
	int l = strlen(temp);
    if(l < 3) 
        return camId;
    int i = 1;
	for(; i < l; i++){
		if(temp[i] != 0) break;
    }
	return atoi(temp+i);
}

int count = 0;


void mcamFrameCallback(FRAME frame, void* data)
{
	if(frame.m_metadata.m_tile == 0){ //when acosd starts with "-s 2", select differenct scales, 0: 3864x2174; 1:1920x1080, otherwise, only 0 is available
		FILE** fileH = static_cast<FILE**>(data);
		fwrite(frame.m_image, 1, frame.m_metadata.m_size, fileH[getOutFileID(frame.m_metadata.m_camId)]);
		fwrite(&frame.m_metadata, 1, sizeof(frame.m_metadata), fileH[getOutFileID(frame.m_metadata.m_camId) + 19]);
	}
}

void printHelp()
{
    printf("Get frame stream:\n");
    printf("Usage:\n");
    printf("\t<Client Port> port connect from(default 13000)\n\n");
    printf("\t<Server Port> port connect to (default 9998)\n\n");
}

int connectToIpsFromSyncFile(char fileName[], int sPort)
{

    FILE* file = fopen(fileName, "r"); /* should check the result */
    ifstream in(fileName);

    printf("in readsync now \n");
    vector<string> Ips;
    string line;
    while (getline(in, line)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s\n", line.c_str()); 
	Ips.push_back(line);
    }
       /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */
    for( int i=0; i<Ips.size(); i++){
	    printf("About to connect to ip %s on port %d \n", Ips[i].c_str(), sPort);
	    mCamConnect(Ips[i].c_str(), sPort);
	    printf("Connected \n");
    }

    in.close();
    return Ips.size();
}

int main(int argc, char* argv[]){
    /****************   read configuration  *****************/ 
    /********************************************************/
    //Parse arguments
    if(argc >1 && strcasecmp(argv[1],"-h") == 0) {
	printHelp();
        return 0;
    }
    char* hostfile = "sync.cfg";
    int cPort = 13000;
    if(argc > 1) cPort = atoi(argv[1]);
    int sPort = 9998;
    if(argc > 2) sPort = atoi(argv[2]);
    printf("Server Port: %d\nClient Port: %d\n", sPort, cPort);

    /**************** Camera Initialization *****************/ 
    /********************************************************/
    /* start stream */
    connectToIpsFromSyncFile(hostfile, sPort);
    /* get cameras from API */
    int numMCams = getNumberOfMCams();
    printf("API reported that there are %d microcameras available\n", numMCams);
    MICRO_CAMERA mcamList[numMCams];
     /* create new microcamera callback struct */
    NEW_MICRO_CAMERA_CALLBACK mcamCB;
    mcamCB.f = newMCamCallback;
    mcamCB.data = mcamList;

    /* call setNewMCamCallback; this function sets a callback that is
     * triggered each time a new microcamera is discovered by the API,
     * and also calls the callback function for each microcamera that
     * has already been discovered at the time of setting the callback */
    setNewMCamCallback(mcamCB);

    /* Next we set a callback function to receive the stream of frames
     * from the desired microcamera */
    MICRO_CAMERA_FRAME_CALLBACK frameCB;
    frameCB.f = mcamFrameCallback;

    //Set output file handles
    char fileName[20] = {0};
    char fileNameConfig[20] = {0};
    vOutFiles.resize(numMCams * 2); 

    for (int i = 0; i < numMCams; i++){

	    printf("CameraId: %d\n", mcamList[i].mcamID);
	    sprintf(fileName,"mcam_%d", mcamList[i].mcamID);
	    sprintf(fileName,"mcam_config_%d", mcamList[i].mcamID);
	    int fileId = getOutFileID(mcamList[i].mcamID);

        // if(fileId >= vOutFiles.size()) {
        //     vOutFiles.resize((fileId + 1) * 2);
        // }
	    
        vOutFiles[fileId] = fopen(fileName, "wb");
        vOutFiles[fileId + numMCams] = fopen(fileNameConfig, "wb");
	    printf("Camera %d saved to %s fileID:%d\n", mcamList[i].mcamID, fileName, fileId);
	    printf("Camera config file %d saved to %s fileID:%d\n", mcamList[i].mcamID, fileNameConfig, fileId);
    }

    frameCB.data = (void*)&vOutFiles[0];
    setMCamFrameCallback(frameCB);
    for (int i = 0; i < numMCams; i++){
	    initMCamFrameReceiver( cPort+i, 1 );
    }


    /*************************************************************/
    /*************************************************************/
    /* For each camera in MCamList start the stream for 10 seconds, then stop it,
        which will allow the frame callback to recieve frames and save the timestamp
       to a file */ 
    for (int i = 0; i < numMCams; i++){
	    //Start the stream
	    if( !startMCamStream(mcamList[i], cPort+i) ){
		    printf("Failed to start streaming mcam %u\n", mcamList[i].mcamID);
		    exit(0);
	    }
	    //if(setMCamWhiteBalance( mcamList[i], 8)){
	    AtlWhiteBalance wb = getMCamWhiteBalance(mcamList[i]);
	    printf("CAM:%d before-- red: %f green: %f blue: %f\n ",mcamList[i].mcamID, wb.red, wb.green, wb.blue);
	    //if(setMCamWhiteBalanceMode( mcamList[i], 3)){
	    //if(setMCamWhiteBalance( mcamList[i], wb)){
	    //	printf("WhiteBalance successfully Set mode to: %d\n", 3);
	    //}
	    sleep(0.2);
    }

    char a;
    scanf("%c", &a);

    printf("start to stop streaming!\n");

    for (int i = 0; i < numMCams; i++){
        //Stop the stream
        if( !stopMCamStream(mcamList[i], cPort+i) ){
            printf("Failed to stop streaming mcam %u\n", mcamList[i].mcamID);
        }
    }


    for (int i = 0; i < numMCams; i++){
    	closeMCamFrameReceiver( cPort+i );
    }

    //close output file handles
    for (int i = 0; i < numMCams; i++){
	    fclose(vOutFiles[getOutFileID(mcamList[i].mcamID)]);
	    fclose(vOutFiles[getOutFileID(mcamList[i].mcamID) + 19]);
    
        AtlWhiteBalance wb = getMCamWhiteBalance(mcamList[i]);
	    printf("CAM: %d after-- red: %f green: %f blue: %f\n",mcamList[i].mcamID, wb.red, wb.green, wb.blue);
    }
    
    printf("%d frames received\n", count);
}
