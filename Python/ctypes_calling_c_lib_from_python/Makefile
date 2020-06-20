.PHONY: all clean clib.o clib.so test

all: test

clean:
	rm -f *.o *.so *.pyc

clib.o: clib.c
	gcc -c -Wall -Werror -fpic clib.c

clib.so: clib.o
	gcc -shared -o libclib.so clib.o

test: clib.so
	./call_clib.py
