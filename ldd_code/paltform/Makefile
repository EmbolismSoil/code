obj-m=$(name).o
CURRENTDIR=$(shell pwd)
KERNELDIR=/lib/modules/$(shell uname -r)/build

module:
	make -C $(KERNELDIR) M=$(CURRENTDIR) modules
clean:
	make -C $(KERNELDIR) M=$(CURRENTDIR) clean
