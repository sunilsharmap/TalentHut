#include <stdio.h>
#include <stdarg.h>

#define NUMARGS(...)  (sizeof((int[]){__VA_ARGS__})/sizeof(int))
#define ADD(...) 	int i = 0;\
					len = NUMARGS(__VA_ARGS__);\
					int arr[] = {__VA_ARGS__};\
					while(i < len){\
					sum = sum + arr[i];\
					i++;}\
					printf("(%d) arguments are passed\nSum of (%d) arguments = %d\n", len, len, sum);

int main()
{
	int sum = 0, len = 0;
	ADD(1, 2, 3, 4, 5, 6, 7, 8);
	return 0;
}

