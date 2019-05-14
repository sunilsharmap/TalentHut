#include <stdio.h>
#include <limits.h>

int main()
{
    int arr[] = {1,1,2,2,3,5,6,4,6,5};
    int size = 10;
    int first, second, i;
    first = second = INT_MIN;

	if(size < 2) {
        printf("Array size is less than two, second largest doesnot exist\n");
    }

	for(i = 0; i < size; i++) {
        if(arr[i] > first) {
            second = first;
            first = arr[i];
        }
        else if((arr[i] > second) && (arr[i] != first)) {
            second = arr[i];
        }
    }

	if(second == INT_MIN)
        printf("Second largest doesnot exist\n");
    else
        printf("Second largest is %d\n", second);
    return 0;
}
