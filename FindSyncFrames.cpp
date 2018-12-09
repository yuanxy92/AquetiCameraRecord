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

int extractSyncFrames(std::vector<std::vector<uint64_t>> timeStamps, 
    std::vector<std::vector<int>>& selectedFrameInds) {
    // go through all the first frame to find the one having largest time stamp
    uint64_t largestTimeStamp = 0;
    for (int i = 0; i < 19; i ++) {
        if (timeStamps[i][0] > largestTimeStamp) {
            largestTimeStamp = timeStamps[i][0];
        }
    }
    printf("Timestamp of the first frame is %llu !\n", largestTimeStamp);
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