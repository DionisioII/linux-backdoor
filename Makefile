#Makefile
ifneq ($(KERNELRELEASE), )
	obj-m := examModule.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/source
	OBJDIR ?= /lib/modules/$(shell uname -r)/build
	PWD = $(shell pwd)
default: 
	$(MAKE) -C $(KERNELDIR) O=$(OBJDIR) M=$(PWD) modules
endif

.PHONY: clean

clean:
	rm -rf *.o *~ *.ko *.mod.c Module.symvers modules.order
