#!/bin/bash
# $1 input dir contains files
# $2 output dir to save outputs
mkdir $2
for((i=1;i<=19;i++));
do
	cmdstr="/media/data/project/AquetiCameraRecord/build/CutH264Stream "$1"/mcam_700"$i" "$2"/mcam_700"$i"
    "$1"/mcam_config_700"$i" "$2"/mcam_config_700"$i" "$2"/mcam_config_700"$i".txt"
	
	echo $cmdstr;
	${cmdstr}
done