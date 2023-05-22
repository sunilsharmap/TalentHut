// Fibonacci series using recursion.

#include<stdio.h>

int fibonacci(int i) {
	if (i == 0) {
		return 0;
	}
	else if (i == 1) {
		return 1;
	}
	else {
		return (fibonacci(i - 1) + fibonacci(i - 2));
	}
}

int main() {
	int n = 10, i;

	printf("fibonacci series:\n");

	for (i = 0; i < n; i++) {
		printf("%d ", fibonacci(i));
	}
}

// Output: 0 1 1 2 3 5 8 13 21 34
