/* Second smallest element in a sorted array */
#include <stdio.h>
#include <limits.h>

int main()
{
	int arr[] = { 3, -2, 0, 10, 1, 2, 3, -4, 5, 6 };
	int size = 10;
	int first=INT_MAX, second=INT_MAX, i = 0;

	if (size < 2) {
		printf("Array size is less than two, second smallest doesnot exist\n");
		return -1;
	}

	for (i; i < size; i++) {
		if (arr[i] < first) {
			second = first;
			first = arr[i];
		}
		else if ((arr[i] < second) && (arr[i] != first)) {
			second = arr[i];
		}
	}

	if (second == INT_MAX) {
		printf("There is no second smallest elemen\n");
	}
	else {
		printf("The second Smallest element is %d\n", second);
	}

	return 0;
}
