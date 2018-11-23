############################################################
# Makefile                                                 #
# Description: Makefile to build the taget linkedlist.out  #
#  Created on: Jun 25, 2018                                #
#      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>   #
############################################################

.PHONY: all clean

CC 		= gcc
C_FLAGS 	= -Wall

APP_FILE 	= main.c
LIB_FILE	= node.c
INC_PATH 	= -I$(PWD)

OUT_FILE 	= linkedlist.out

all:
	clear # Cleare the screen before proceeding
	@echo ""
	$(CC) $(C_FLAGS) $(INC_PATH) $(APP_FILE) $(LIB_FILE) -o $(OUT_FILE)
	@echo ""

clean:
	@echo ""
	rm -rf $(OUT_FILE)
	@echo ""
