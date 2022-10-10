############################################################
# Makefile                                                 #
# Description: Makefile to build the taget linkedlist.out  #
#  Created on: Jun 25, 2018                                #
#      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>   #
############################################################

.PHONY: all clean main.o node.o libsll.so mkdir

CC        = gcc
C_FLAGS   = -c -Wall -Werror -fPIC

APP_FILE  = src/cli/main.c
LIB_FILE  = src/node.c
INC_PATH  = -Iinclude

all: mkdir libsll.so main.o
        @$(CC) -Wl,-rpath,\$$ORIGIN/../lib build/main.o $(INC_PATH) -Lbuild/lib -lsll -o build/bin/sll_cli
        @echo "Make completed"

main.o:
        @$(CC) $(APP_FILE) $(INC_PATH) -c -o build/main.o

node.o:
        @$(CC) $(C_FLAGS) $(LIB_FILE) $(INC_PATH) -o build/node.o

libsll.so: node.o
        @$(CC) -shared build/node.o -o build/lib/libsll.so

mkdir:
        @mkdir -p build/bin build/lib

clean:
        @rm -rf $(OUT_FILE) main.o node.o libsll.so build
        @echo "Make clean completed"
