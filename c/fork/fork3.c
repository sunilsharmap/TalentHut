# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>

# define CHILD 0
int childstatus;
void sighand(int signum){
	printf(" I am in sig handler \n");
	wait(&childstatus);
}

main(){
        pid_t pid;	
	pid = fork();
	if( pid == CHILD){
	printf(" I am in child task \n");
	}
	// parent
	else{
                printf ("i am in parent \n");
		signal(SIGCHLD,sighand);
		while(1);
	}
}
