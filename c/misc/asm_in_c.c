#include<stdio.h>
/* This is Architecture dependent. The registers vary wrt architecture. */
int main()
{
	int c = 0;
	int a;
	asm(
		"movl $100,0x00(%esp);"
		"movl $200,0x04(%esp);"
		"movl 0x00(%esp),%eax;"
		"movl 0x04(%esp),%edx;"
		"addl %edx,%eax;"
		"movl %eax,0x20(%esp);"
	);
	printf("Sum is %d\n", c);
	return 0;
}
