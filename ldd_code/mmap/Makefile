obj-m=mmap.o
CURRENTDIR=$(shell pwd)
KERNELDIR=/lib/modules/$(shell uname -r)/build

module:
	make -C $(KERNELDIR) M=$(CURRENTDIR) modules
	
	insmod mmap.ko || rmmod mmap && insmod mmap.ko
	sleep 5 && dmesg | tail -1 >> ./user_test.c &
	
user.d:user.c
	gcc -M $< > $@.$$$$
user:test.out
	gcc -g user.c -o user.out 
test.out:user_test.c
	gcc -g user_test.c -o  test.out

clean:
	make -C $(KERNELDIR) M=$(CURRENTDIR) clean
	rm *.out
