# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
main(int argc,char *argv[],char *envp[]){
	int i;
	printf(" No of arguments = %d\n",argc);
	/*for(i=0;i<argc;i++)
		printf("%d    %s\n",i,argv[i]);
	i=0;*/
        for(i=0;argv[i]!=NULL;i++)
        printf("%d  %s \n",i,argv[i]);
       i=0;
	while(1)
{
		if(envp[i] == NULL)
			break;
		printf("%s\n",envp[i]);
		i++;
	}
}
