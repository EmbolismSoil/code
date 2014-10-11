obj-m=kobj.o
CURRENTDIR=$(shell pwd)
KERNELDIR=/lib/modules/$(shell uname -r)/build
all:
	make -C $(KERNELDIR) M=$(CURRENTDIR) modules
	insmod kobj.ko || rmmod kobj.ko && insmod kobj.ko
clean:
	make -C $(KERNELDIR) M=$(CURRENTDIR) clean
	rmmod kobj.ko
