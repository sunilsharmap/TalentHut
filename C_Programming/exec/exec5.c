# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	printf("Can you see me [ONE]\n");
	execl("./test","arg1","arg2",NULL);	
	printf("Can you see me [TWO]\n");
}
