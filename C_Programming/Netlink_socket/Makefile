obj-m += netlink_kernel.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KDIR)  M=$(shell pwd) modules
	@gcc -o user.out netlink_user.c -Wall
	@echo "Done"

clean:
	@make -C $(KDIR)  M=$(shell pwd) clean
	@rm -rf user.out
	@echo "Done"
