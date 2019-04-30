.PHONY: all clean

all:
	@gcc -Wall msgq_server.c -oserver.out
	@gcc -Wall msgq_client.c -oclient.out
	@echo "make all successful"

clean:
	@rm -f server.out client.out
	@echo "make clean successful"
