#include <stdio.h>
#include <stdint.h>

int main()
{
    uint32_t UserInput = 0;
    uint32_t ScanRet = 0;
    while (1) {
        printf("Enter the option\n");
        printf("1 - Print \"1\"\n");
        printf("2 - Print \"2\"\n");
        printf("3 - Print \"3\"\n");
        ScanRet = scanf("%d", &UserInput);
        if(ScanRet != 1) {
            printf("ERROR!! Input is not proper\n");
            getchar();
        } else {
            getchar();
            switch(UserInput) {
                case 1: printf("1\n"); break;
                case 2: printf("2\n"); break;
                case 3: printf("3\n"); break;
                default: printf("Default\n"); break;
            }
        }
    }
    return 0;
}
