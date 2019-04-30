#!/bin/bash
for((i=1;i<=1;i++));
do
	cmdstr="./process_raw_stream.sh data_"$i" data_"$i"_cut data_"$i"_mp4"
	echo $cmdstr
	${cmdstr}
done
