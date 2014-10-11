#!/bin/bash
gdialog --title "choice" --yesno "you wanna insmod this module after compile ?" 

if [ $? == 0 ];then
NAME=$(ls | grep "c" | sed "s/.c//g")
make name=$NAME
insmod $NAME.ko
fi
exit 0 || exit 1
