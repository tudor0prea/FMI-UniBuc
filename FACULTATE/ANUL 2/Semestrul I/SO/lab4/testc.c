#include <sys/types.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int main( int argc, char **arg) {

pid_t pid;


for(int i=1;i<argc;i++)
	{ pid=fork();
	if(pid < 0 ) {printf("ERROR"); return 0; }
	else if(pid==0)
		{ printf("CHILD PID=%d\n", getpid());
		int n= atoi(arg[i]);
		//printf("%d",n);
		
		
		while(n!=1) {
			if(n%2) n=3*n+1;
			else n=n/2; 
			printf("%d ",n); }
		
		printf("PARENT PID=%d\n",getpid());
		return 0;
		}
		//asa le am opri dupa ce se executa imediat
		// else { wait(NULL); printf("CHILD PID=%d\n", getpid()); }
}

if(pid>0)
for(int i=1;i<argc;i++)
{	int chpid=wait(NULL);
	printf("Done Parent %d Me %d\n", getpid(),chpid);
}
return 0;}

	
