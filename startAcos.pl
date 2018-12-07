#!/usr/bin/perl
open(HOSTIP, "sync.cfg") or die("Cant find file sync.cfg");
while(<HOSTIP>){
        s/\s$//;
	system("ssh nvidia@".$_." -t 'kill -9 `pgrep acosd`;sleep 10; acosd -C H264 -s 2 -p 9999'");
}
close(HOSTIP);
