/*
 * File       : even_odd_thread_cond_var.c
 * Description: One thread will print even numbers and other thread will
 * 				print odd numbers and its ordered(syncronized)
 * Compile    : gcc even_odd_thread_cond_var.c -o thread.out -lpthread
 * 				(Add -DDEBUG to eneble debug prints in `Compile`)
 * Run        : ./thread.out
 * reference  : https://freethreads.net/2012/05/05/two-indepedent-threads-to-print-even-and-odd-numbers-in-c/
 * 				(Modified the code for better readability)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef DEBUG
    #define debug_printf(...)
#else
    #define debug_printf(...) printf (__VA_ARGS__)
#endif

#define COUNT_DONE 10

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

/* Shared resource */
int count = 0;

/* Print odd numbers */
void *odd_print()
{
	for(;;) {
		debug_printf("Odd waiting for lock\n");
		pthread_mutex_lock( &count_mutex );
		debug_printf("Odd locked\n");
		
		if ( count >= COUNT_DONE ) {
			pthread_cond_signal( &condition_var );	   
			pthread_mutex_unlock( &count_mutex );
			debug_printf("Odd Done Cond Mutex unlock\n");
			return(NULL);
		}

		if ( count % 2 == 0 ) {
			debug_printf("Odd waiting for cond\n");
			pthread_cond_wait( &condition_var, &count_mutex );
			debug_printf("Odd cond got\n");
		}

		printf("Odd  : %d\n",count);
		count++;
		pthread_cond_signal( &condition_var );
		debug_printf("Odd waiting for unlock\n");
		pthread_mutex_unlock( &count_mutex );
		debug_printf("Odd unlocked\n");
	}
}

/* print even numbers */
void *even_print()
{
	for(;;) {
		debug_printf("Even waiting for lock\n");
		pthread_mutex_lock( &count_mutex );
		debug_printf("Even locked\n");
		
		if( count >= COUNT_DONE ) {
			pthread_cond_signal( &condition_var );
			pthread_mutex_unlock( &count_mutex );
			debug_printf("Even Done Cond Mutex unlock\n");
			return(NULL);
		}
		
		if ( count % 2 != 0 ) {
			debug_printf("Even waiting for cond\n");
			pthread_cond_wait( &condition_var, &count_mutex );
			debug_printf("Even cond got\n");
		}

		printf("Even : %d\n",count);
		count++;
		pthread_cond_signal( &condition_var );
		debug_printf("Even waiting for unlock\n");
		pthread_mutex_unlock( &count_mutex );
		debug_printf("Even unlocked\n");
	}
}

int main()
{
	pthread_t thread1, thread2;

	pthread_create( &thread1, NULL, &odd_print, NULL);
	pthread_create( &thread2, NULL, &even_print, NULL);

	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);

	return 0;
}

