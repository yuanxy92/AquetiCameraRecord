#!/bin/bash
# $1 input dir contains raw data files
# $2 output dir to save cutted stream files
# $3 output dir to save mp4 file and sync files
./cut_h264_stream.sh $1 $2
./decode.sh $2 $3
./build/FindSyncFrames $2 $3/sync.txt