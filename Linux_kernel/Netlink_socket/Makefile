#####################################################################
# netlink_user.c
#
# Description: https://stackoverflow.com/questions/3299386/how-to-use-netlink-socket-to-communicate-with-a-kernel-module
#              http://opensourceforu.com/2015/08/netlink-a-communication-mechanism-in-linux/
#
#  Created on: 04-Mar-2020
#      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
#
#     Version: 1.0v
#####################################################################

obj-m := netlink_kernel.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	@make -C $(KDIR)  M=$(shell pwd) modules
	@gcc -o user.out netlink_user.c -Wall
	@echo "Done"

clean:
	@make -C $(KDIR)  M=$(shell pwd) clean
	@rm -rf user.out
	@echo "Done"
