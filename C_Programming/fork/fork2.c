# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/wait.h>

# define CHILD 0
static int k=10;
main(){
       pid_t pid;	
	int childstatus;
	//static int k=10;
//	printf(" My pid = %d \n", getpid());
//	getchar();
	pid = fork();
	if( pid == CHILD){
		printf(" child: My pid = %d \n", getpid());
		printf(" end of child k = %d\n",k);
		k=44;
		printf(" end of child k = %d\n",k);
               exit(1);
	}
	// parent
	else{
		printf(" My pid = %d \n", getpid());
		printf(" Newly created child pid = %d \n", pid);
		wait(&childstatus);
		printf("end of parent k = %d\n",k);
		printf("Child status = %d\n",WEXITSTATUS(childstatus));
	}
}
		
