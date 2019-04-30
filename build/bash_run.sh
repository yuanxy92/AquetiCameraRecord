#!/bin/bash
for((i=1;i<=1;i++));
do
	cmdstr="./process_raw_stream.sh /media/luvision/SamsungDisk/data/test_"$i" /media/luvision/SamsungDisk/data/test_"$i"_cut /media/luvision/SamsungDisk/data/test_"$i"_mp4"
	echo $cmdstr
	${cmdstr}
done
