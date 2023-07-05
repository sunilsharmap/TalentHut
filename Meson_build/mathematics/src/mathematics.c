#include <mathematics.h>

int32_t addition(int32_t num1, int32_t num2)
{
    return (num1 + num2);
}

int32_t subtraction(int32_t num1, int32_t num2)
{
    return (num1 - num2);
}

int32_t multiplication(int32_t num1, int32_t num2)
{
    return (num1 * num2);
}

int32_t division_q(int32_t num1, int32_t num2)
{
    if(num2 != 0){
        return (num1 / num2);
    }
    else {
        return 1;
    }
}

int32_t division_r(int32_t num1, int32_t num2)
{
    if(num2 != 0){
        return (num1 % num2);
    }
    else {
        return 1;
    }
}