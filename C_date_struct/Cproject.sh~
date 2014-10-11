#!/bin/bash
export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/Brooks/x-tools/arm-lee-linux-gnueabi/bin

SRC=$(ls -l | sed "s/.* //g" | grep "\.[cCsS]$")
BAK=$(ls -l | sed "s/.* //g" | grep "~$")
INC=$(ls -l | sed "s/.* //g" | grep "\.[hH]$")

[ -d ./inc ] || mkdir inc
[ -d ./src ] || mkdir src
[ -d ./bak ] || mkdir bak

echo "mv $SRC to src/"
echo "mv $BAK to bak/"
echo "mv $INC to inc/"
mv $SRC src
mv $BAK bak
mv $INC inc
