obj-m=globalmem.o
CURRENTDIR=$(shell pwd)
KERNELDIR=/lib/modules/$(shell uname -r)/build

module:
	make -C $(KERNELDIR) M=$(CURRENTDIR) modules
	if[-e /sys/module/globalmem/] then
	echo "aaa"
	fi	
	
	gcc -g user_test.c -o  test.out
	
clean:
	make -C $(KERNELDIR) M=$(CURRENTDIR) clean
	rm *.out
