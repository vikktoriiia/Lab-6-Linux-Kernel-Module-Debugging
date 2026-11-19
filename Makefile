obj-m += hello1.o
obj-m += hello2.o

ccflags-y := -I$(src)/inc
ccflags-y += -g -O0

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

