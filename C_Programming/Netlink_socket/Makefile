obj-m += netlink_kernel.o

KDIR = /lib/modules/$(shell uname -r)/build
 
all:
	@make -C $(KDIR)  M=$(shell pwd) modules
	@echo "**** Module build success ****"
	@gcc -o user.out netlink_user.c -Wall
	@echo "**** User Application build success ****"

clean:
	@make -C $(KDIR)  M=$(shell pwd) clean
	@rm -rf user.out
	@echo "**** Module Clean success ****"
