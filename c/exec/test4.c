
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

main(){
	printf(" Can you see this 1 out \n");
	perror("Can you see this... 2 error \n");
}
