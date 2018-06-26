#include <stdio.h>
#include "shared.h"

int main()
{
    int a = 0;
    int b = 0;
    printf("Enter two numbers:\n");
    scanf("%d %d", &a, &b);
    /* \e[1;32m and \e[0m for printing green color text */
    printf("\e[1;32mSum of %d and %d is %d\e[0m\n", a, b, addition(a, b));
    return 0;
}
