#!/bin/bash
mkdir $2
for((i=1;i<=19;i++));
do
	cmdstr="ffmpeg -framerate 30 -i "$1"/mcam_700"$i" -c copy "$2"/mcam_700"$i".mp4"
	
	echo $cmdstr;
	${cmdstr}
done
