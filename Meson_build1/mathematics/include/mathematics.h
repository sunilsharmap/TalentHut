#pragma once

#include <stdio.h>
#include <stdint.h>

#include "extern.h"

LIB_EXTERN int32_t addition(int32_t num1, int32_t num2);
LIB_EXTERN int32_t subtraction(int32_t num1, int32_t num2);
LIB_EXTERN int32_t multiplication(int32_t num1, int32_t num2);
LIB_EXTERN int32_t division_r(int32_t num1, int32_t num2);
LIB_EXTERN int32_t division_q(int32_t num1, int32_t num2);