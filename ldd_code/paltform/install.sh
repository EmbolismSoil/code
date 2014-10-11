#!/bin/bash
if [ -z $1 ];then
echo "please input your cmd"
exit 0
fi
case "$1" in
"install") 
if [ -z $2 ];then
echo "please input the module's name"
exit 0
fi

if [ -e /sys/module/$2 ] ;then
rmmod $2 && echo "rmmod ....OK" 
insmod $2.ko && echo "rmmod & insmod .....OK" 
else
insmod $2.ko && echo "insmod ...OK"
fi
exit 0 ;;

"uninstall")
if [ -z $2 ];then
echo "please input the module's name"
exit 0
fi

if [ -e /sys/module/$2 ] ;then
rmmod $2 && echo "rmmod ....OK"  
else
echo "module is not exist"
fi
exit 0 ;;

esac
