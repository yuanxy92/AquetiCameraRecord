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

int findIframePosition(std::string metafile) {
    FILE *fpmeta;
    // open meta file for read
    fpmeta = fopen(metafile.c_str(), "rb");
    FRAME_METADATA frameInfo;
    int result;

    int IframeInd = 0;
    unsigned int maxFrameSize = 0;

    for(int i = 0; i < 30; i ++) {
        result = fread(&frameInfo, 1, sizeof(frameInfo), fpmeta);
        if (result != sizeof(frameInfo))
            break;
        if (frameInfo.m_size > maxFrameSize) {
            IframeInd = i;
            maxFrameSize = frameInfo.m_size;
        }

    }
    fclose(fpmeta);
    printf("Frame index %d is an I frame!\n", IframeInd);
    return IframeInd;
}

int findIframePosition2(std::string h264file, std::string metafile) {
    FILE *fpmeta, *fph264;
    // open meta file for read
    fpmeta = fopen(metafile.c_str(), "rb");
    fph264 = fopen(h264file.c_str(), "rb");
    FRAME_METADATA frameInfo;
    int result;
    char* data;
    int IframeInd = 0;
    int ind = 0;
    for(;;) {
        result = fread(&frameInfo, 1, sizeof(frameInfo), fpmeta);
        if (result != sizeof(frameInfo))
            break;
        data = new char[frameInfo.m_size];
        if(!fread(data, 1, frameInfo.m_size, fph264)) {
            printf("Read h264 stream file failed.\n");
            exit(-1);
        }
        if (data[4] == 0x67 and data[5] == 0x64) {
            IframeInd = ind;
            break;
        }
        delete[] data;
        ind ++;
    }
    fclose(fph264);
    fclose(fpmeta);
    printf("Frame index %d is an I frame!\n", IframeInd);
    return IframeInd;
}

int cutHEVCStream(std::string h264file, std::string h264file_out, 
    std::string metafile, std::string metafile_out, std::string metafile_out_txt, int IframeInd) {
    // std::string h264file = "/media/data/project/AquetiCameraRecord/data/1/mcam_7001";
    // std::string h264file_out = "/media/data/project/AquetiCameraRecord/data/1/mcam_7001_cut";
    // std::string metafile = "/media/data/project/AquetiCameraRecord/data/1/mcam_config_7001";
    // std::string metafile_out = "/media/data/project/AquetiCameraRecord/data/1/mcam_config_7001_cut";

    FILE *fph264, *fph264_out, *fpmeta, *fpmeta_out, *fpmeta_out_txt;

    // open meta file for read
    fpmeta = fopen(metafile.c_str(), "rb");
    FRAME_METADATA frameInfo;
    // open h264 stream file for read
    fph264 = fopen(h264file.c_str(), "rb");
    char* data;

    // open meta file for write
    fpmeta_out = fopen(metafile_out.c_str(), "wb");
    // open h264 stream file for write
    fph264_out = fopen(h264file_out.c_str(), "wb");

    // open text meta file for write
    fpmeta_out_txt = fopen(metafile_out_txt.c_str(), "w");

    int result;
    int ind = 0;
    int valid_frame_num = 0;
    bool hasIframe = false;
    for(;;) {
        result = fread(&frameInfo, 1, sizeof(frameInfo), fpmeta);
        if (result != sizeof(frameInfo))
            break;
        printf("%d\t%zu\t%llu\n", ind, frameInfo.m_size, frameInfo.m_timestamp);

        data = new char[frameInfo.m_size];
        if(!fread(data, 1, frameInfo.m_size, fph264)) {
            printf("Read h264 stream file failed.\n");
            exit(-1);
        }

        if (!hasIframe && ind == IframeInd) {
            printf("Frame index %d is an I frame!\n", ind);
            hasIframe = true;
        }

        if (hasIframe) {
            fwrite(data, frameInfo.m_size, 1, fph264_out);
            fwrite(&frameInfo, sizeof(frameInfo), 1, fpmeta_out);
            fprintf(fpmeta_out_txt, "%d\t%zu\t%llu\n", valid_frame_num, frameInfo.m_size, frameInfo.m_timestamp);
            valid_frame_num++;
        }
        delete[] data;

        ind ++;

    }

    fclose(fph264);
    fclose(fpmeta);
    fclose(fph264_out);
    fclose(fpmeta_out);
    fclose(fpmeta_out_txt);

    printf("Cut video finished, total %d frames!\n", valid_frame_num);

    return 0;
}

int main(int argc, char* argv[]) {
    //int IframeInd1 = findIframePosition(argv[3]);
    //int IframeInd2 = findIframePosition2(argv[1], argv[3]);
    //printf("Method 1, I frame is %d, Method 2, I frame is %d\n", IframeInd1, IframeInd2);

    int IframeInd = findIframePosition2(argv[1], argv[3]);
    cutHEVCStream(argv[1], argv[2], argv[3], argv[4], argv[5], IframeInd);
    return 0;
}