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
    for (int i = 0; i < 19; i ++) {
        if (timeStamps[i][0] > largestTimeStamp) {
            largestTimeStamp = timeStamps[i][0];
        }
    }
    printf("Timestamp of the first frame is %llu !\n", largestTimeStamp);
    // find inds for each h264 stream
    selectedFrameInds.resize(19);
    uint64_t eps = 33000 / 2; 
    for (int i = 0; i < 19; i ++) {
        for (int ind = 0; ind < timeStamps[i].size(); ind ++) {
            uint64_t dist = timeStampDist(largestTimeStamp, timeStamps[i][ind]);
            if (dist < eps) {
                if (ind < timeStamps[i].size() - 1) {
                    uint64_t dist2 = timeStampDist(largestTimeStamp, timeStamps[i][ind + 1]);
                    if (dist < dist2)
                        selectedFrameInds[i].push_back(ind);
                    else selectedFrameInds[i].push_back(ind + 1);
                }
                else selectedFrameInds[i].push_back(ind);
                break;
            }
        }
    }
    // output information
    for (int i = 0; i < 19; i ++) {   
        printf("Stream %d has %lu frames, starts from index %d, has valid frames %d\n", i, timeStamps[i].size(),
            selectedFrameInds[i][0], timeStamps[i].size() - selectedFrameInds[i][0]);
    }

    // start to find 
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