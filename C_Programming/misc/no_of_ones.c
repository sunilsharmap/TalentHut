#include <stdio.h>

int find_no_of_ones (int num)
{
	int count = 0;
	while(num) {
		num &= (num - 1);
		count += 1;
	}   
	return count;
}

int main(int argc, char *argv[])
{  
	int number = 0;
	int ones_count = 0;
	printf("Enter the Number:");
	scanf("%d", &number);
	printf("You enterd %d\n", number);

	ones_count = find_no_of_ones(number);
	printf("\nNo. of SET bits in %d is/are %d\n\n", number, ones_count);
	return 0;
}
