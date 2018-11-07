/*
 * This code is taken from https://www.geeksforgeeks.org/functions-that-are-executed-before-and-after-main-in-c/
 * All rights of this code belongs to www.geeksforgeeks.org.
 */
 
#include<stdio.h> 
  
/* Apply the constructor attribute to myStartupFun() so that it 
    is executed before main() */
void myStartupFun (void) __attribute__ ((constructor)); 
  
  
/* Apply the destructor attribute to myCleanupFun() so that it 
   is executed after main() */
void myCleanupFun (void) __attribute__ ((destructor)); 
  
  
/* implementation of myStartupFun */
void myStartupFun (void) 
{ 
    printf ("startup code before main()\n"); 
} 
  
/* implementation of myCleanupFun */
void myCleanupFun (void) 
{ 
    printf ("cleanup code after main()\n"); 
} 
  
int main (void) 
{ 
    printf ("main() function execution\n"); 
    return 0; 
}
