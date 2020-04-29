obj-m := kernel_ioctl.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KDIR)  M=$(shell pwd) modules
	@gcc -Wall user_ioctl.c -o user_ioctl.out
	@echo "Make Done"

clean:
	@make -C $(KDIR)  M=$(shell pwd) clean
	@rm -f user_ioctl.out
	@echo "Clean Done"
