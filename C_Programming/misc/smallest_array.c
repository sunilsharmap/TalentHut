/*
 * smallest_array.c
 *
 * Description:
 *              Input : x = 5, y = 7, z = 11
 *              Output : 7
 *              The smallest starts with 5, having 7, ends
 *              with 11 and having absolute difference 1
 *              is { 5, 6, 7, 8, 9, 10, 11 }.
 *
 *              Input : x = 3, y = 1, z = 2
 *              Output : 4
 *              The array would become { 3, 2, 1, 2 }
 *
 *  Created on: 12-May-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include <stdio.h>
#include <stdlib.h>   /* For abs() */

/* Return the size of smallest array with given constraint. */
int min_array_length(int x, int y, int z)
{
	return (1 + abs(x - y) + abs(y - z));
}

int main(int argc, char *argv[])
{
	int x = 3, y = 1, z = 2;
	int min_size = 0;
	min_size =  min_array_length(x, y, z);
	printf("The smallest array can be formed by given x = %d, y = %d, & z = %d constaint is of size %d\n", x, y, z, min_size);
	return 0;
}
