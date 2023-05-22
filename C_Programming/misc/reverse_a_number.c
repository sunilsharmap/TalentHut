// C program to reverse a number

#include <stdio.h>
int main()
{
	int n = 123456789, reverse = 0;
	printf("Before Reverse = %d\n", n);

	while (n != 0) {
		reverse = (reverse * 10) + (n % 10);
		n = n / 10;
	}

	printf("After Reverse  = %d", reverse);
	return 0;
}


// Output: 987654321
