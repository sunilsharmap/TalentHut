/*
 * This code is taken from https://www.geeksforgeeks.org/functions-that-are-executed-before-and-after-main-in-c/
 * All rights of this code belongs to www.geeksforgeeks.org.
 */
 
#include<stdio.h> 
  
/* Apply the constructor attribute to myStartupFun() so that it 
    is executed before main() */
void my_startup_fun (void) __attribute__ ((constructor)); 
  
  
/* Apply the destructor attribute to myCleanupFun() so that it 
   is executed after main() */
void my_cleanup_fun (void) __attribute__ ((destructor)); 
  
  
/* implementation of myStartupFun */
void my_startup_fun (void) 
{ 
    printf ("startup code before main()\n"); 
} 
  
/* implementation of myCleanupFun */
void my_cleanup_fun (void) 
{ 
    printf ("cleanup code after main()\n"); 
} 
  
int main (void) 
{ 
    printf ("main() function execution\n"); 
    return 0; 
}
