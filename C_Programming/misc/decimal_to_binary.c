// Covert the given Decimal numner into Binary

#include <stdio.h>
#include <stdint.h>

uint64_t dec_to_bin(int n)
{
	uint64_t binary = 0;
	int remainder;
	int i;
	for (i = 1; n != 0; i = i * 10)
	{
		/* get the remainder */
		remainder = n % 2;

		/* remove the last digit */
		n /= 2;

		/* populate the binary number in the correct position */
		binary += remainder * i;
	}
	return binary;
}

int main()
{
	int n = 100;
	printf("Equivalent binary number: %d\n", dec_to_bin(n));
	return 0;
}
