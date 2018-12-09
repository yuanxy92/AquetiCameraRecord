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

int readTimeStamps(char* dir, std::vector<std::vector<uint64_t>>& timeStamps) {
    timeStamps.resize(19);
    char filename[200];
    for (int i = 0; i < 19; i ++) {
        sprintf(filename, "%s/mcam_config_700%d", dir, i + 1);
        FILE* fp;
        fp = fopen(filename, "rb");
        FRAME_METADATA frameInfo;
        int result;
        int ind = 0;
        for(;;) {
            result = fread(&frameInfo, 1, sizeof(frameInfo), fp);
            if (result != sizeof(frameInfo))
                break;
            //printf("%d\t%lu\t%lu\n", ind, frameInfo.m_type, frameInfo.m_timestamp);
            timeStamps[i].push_back(frameInfo.m_timestamp);
            ind ++;
        }
        fclose(fp);
    }
    return 0;
}

inline int timeStampDist(uint64_t t1, uint64_t t2) {
    return t1 > t2 ? t1 - t2 : t2 - t1;
}

int extractSyncFrames(std::vector<std::vector<uint64_t>> timeStamps, 
    std::vector<std::vector<int>>& selectedFrameInds) {
    // go through all the first frame to find the one having largest time stamp
    uint64_t largestTimeStamp = 0;
    uint64_t smallestTimeStamp = timeStamps[0][0];
    for (int i = 0; i < 19; i ++) {
        if (timeStamps[i][0] > largestTimeStamp) {
            largestTimeStamp = timeStamps[i][0];
        }
        if (timeStamps[i][0] < smallestTimeStamp) {
            smallestTimeStamp = timeStamps[i][0];
        }
    }
    printf("Timestamp of the first frame is %llu !\n", largestTimeStamp);
    // find inds for each h264 stream
    selectedFrameInds.resize(19);
    uint64_t eps = 100000 / 6; 
    for (int i = 0; i < 19; i ++) {
        for (int ind = 0; ind < timeStamps[i].size(); ind ++) {
            uint64_t dist = timeStampDist(largestTimeStamp, timeStamps[i][ind]);
            if (dist < eps) {
                if (ind < timeStamps[i].size() - 1) {
                    uint64_t dist2 = timeStampDist(largestTimeStamp, timeStamps[i][ind + 1]);
                    if (dist < dist2) {
                        selectedFrameInds[i].push_back(ind);
                        printf("Stream %d select %dth frame\n", i, ind);
                    }
                    else {
                        selectedFrameInds[i].push_back(ind + 1);
                        printf("Stream %d select %dth frame\n", i, ind + 1);
                    }
                }
                else selectedFrameInds[i].push_back(ind);
                break;
            }
        }
    }

    // init first frame
    std::vector<int> curInds(19);
    uint64_t startTime = smallestTimeStamp;
    int curTime = 0;
    int meanTime = 0;
    for (int i = 0; i < 19; i ++) {
        meanTime += (int)(timeStamps[i][selectedFrameInds[i][0]] - startTime);
        curInds[i] = selectedFrameInds[i][0] + 1;
    }
    meanTime /= 19;
    curTime = meanTime;

    printf("Current time is %d\n", curTime);
    
    bool lastframe = false;

    // output information
    for (int i = 0; i < 19; i ++) {   
        printf("Stream %d has %lu frames, starts from index %d, has valid frames %d, current shift %d\n",
            i, timeStamps[i].size(), selectedFrameInds[i][0], (int)timeStamps[i].size() - selectedFrameInds[i][0],
                (int)(timeStamps[i][selectedFrameInds[i][0]] - startTime) - curTime);
    }

    curTime += 100000 / 3;

    int frameInd = 1; 
    for (;;) {
        // find index with the best time stamp
        bool passsync = true;
        for (int i = 0; i < 19; i ++) {
            int dist;
            uint64_t ts1 = timeStamps[i][curInds[i]] - startTime;
            int dist1 = timeStampDist(ts1, curTime);
            if (curInds[i] < timeStamps[i].size()) {
                uint64_t ts2 = timeStamps[i][curInds[i] + 1] - startTime;
                int dist2 = timeStampDist(ts2, curTime);
                if (dist2 < dist1) {
                    curInds[i]++;
                    dist = dist2;
                }
                else dist = dist1;
            }
            if (dist > eps) {
                passsync = false;
                break;
            }
        }
        // add new frame
        if (passsync == true) {
            printf("\nSelect new frame %d:\n", frameInd);
            frameInd ++;
            for (int i = 0; i < 19; i ++) {
                selectedFrameInds[i].push_back(curInds[i]);
                printf("Stream %d select %dth frames, time shift%d\n", i, curInds[i],
                    (int)(timeStamps[i][curInds[i]] - startTime) - curTime);
                curInds[i]++;
            }
        }
        else {

            for (int i = 0; i < 19; i ++) {
                uint64_t ts = timeStamps[i][curInds[i]] - startTime;
                if (ts > curTime && timeStampDist(ts, curTime) > eps) {
                    // do nothing
                }
                else {
                    curInds[i]++;
                }
            }   
        }

        // check if last frame
        for (int i = 0; i < 19; i ++) {
            if (curInds[i] == timeStamps[i].size())
                lastframe = true;
        }
        if (lastframe == true)
            break;
        
        curTime += 100000 / 3;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    char* dir = "/Users/ShaneYuan/Downloads/data";
    std::vector<std::vector<uint64_t>> timeStamps;
    std::vector<std::vector<int>> selectedFrameInds;
    readTimeStamps(dir, timeStamps);
    extractSyncFrames(timeStamps, selectedFrameInds);
    return 0;
}