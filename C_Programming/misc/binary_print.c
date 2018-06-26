/*
 * binary_print.c
 *
 *  Created on: 09-Oct-2015
 *      Author: sunilpatlamane
 */

#include <stdio.h>

void binary_print(int num);/*to print the number in binary form*/

int main()
{
	int num;
	printf("Enter decimal number you want get the binary equivalent\n");
	scanf("%d", &num);
	printf("Binary equivalent of decimal %d is ", num);
	binary_print(num);
	return 0;
}

void binary_print(int num)
{
	int i, num1 =num;
	for(i=0; i<16; i++){
		num = num<<i;
		num = num & 0x8000;
		if(num){
			printf("1");
		}
		else{
			printf("0");
		}
			num = num1;
	}
	printf("\n");
}
