#!/bin/bash
export PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/home/Brooks/x-tools/arm-lee-linux-gnueabi/bin

SRC=$(ls -l | sed "s/*. //g" | grep ".[cCsS]$")
BAK=$(ls -l | sed "s/*. //g" | grep "~$")
INC=$(ls -l | sed "s/*. //g" | grep ".[hH]$")

[ -d ./include ] && echo "been!"
