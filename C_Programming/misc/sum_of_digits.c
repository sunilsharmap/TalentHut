//C Program to add the digits of a given number using recursive function

#include<stdio.h>

int sum_of_digits(int num) {
	static int sum = 0;
	int rem;
	sum = sum + (num % 10);
	rem = num / 10;
	if (rem > 0) {
		sum_of_digits(rem);
	}
	return sum;
}
int main() {
	int j, num = 123456789;
	printf("Sum of digits of the number %d = %d\n", num, sum_of_digits(num));
}

// Sum of digits of the number 123456789 = 45
