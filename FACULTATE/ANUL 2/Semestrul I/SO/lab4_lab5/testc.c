#include <sys/types.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


int main( int argument, char **arg) {


char shm_name [] = " fisier_comun ";
int shm_fd ;
shm_fd = shm_open ( shm_name , O_CREAT | O_RDWR , S_IRUSR | S_IWUSR );
if ( shm_fd < 0) {
perror ( NULL );
return errno ;
}

size_t shm_size = 1000;

if ( ftruncate ( shm_fd , shm_size ) == -1) {
perror ( NULL );
shm_unlink ( shm_name );
return errno ;
}

for(int i=1;i<=argument;i++)
	{ pid_t pid=fork();
	if(pid < 0 ) {printf("ERROR"); return 0; }
	else if(pid==0)
		{ int n= atoi(arg[i]);
		printf("%d",n);
		
		while(n!=1) {
			if(n%2) n=3*n+1;
			else n=n/2; 
			printf("%d ",n); }
		
		printf("\nPARENT PID=%d\n",getpid());
		return 0;
		}
		else { wait(NULL); printf("CHILD PID=%d\n", getpid()); }
}
return 0;}
	
