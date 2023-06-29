#include <sys/types.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main( int argument, char **arg) {

pid_t pid = fork();

if(argument < 2 ) return 0;

int n = atoi (arg[1]);

if( pid < 0 ) { printf("EROARE"); return 0; }

else if( pid !=0 && n>1 )
	{char *arg2[]={"collatz",arg[1], NULL};
	
	execve("bin/fork",arg2, NULL); 
	
	printf("%d ",n);
	while(n!=1) {
		if(n%2) n=3*n+1;
		else n=n/2; 
		printf("%d ",n); }
	
	
	}
	
	else { wait(NULL); printf("CHILD PID= %d\n", getpid()); }
	
return 0; 
}




