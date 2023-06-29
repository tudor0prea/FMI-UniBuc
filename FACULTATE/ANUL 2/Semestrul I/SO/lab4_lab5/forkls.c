#include <sys/types.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int  main() {

pid_t pid = fork ();

if ( pid < 0 ) 
	{ printf("Eroare\n"); return 0; }
else if ( pid == 0 )
	{//char *argv[]={"ls",NULL};
	execlp("ls", "ls" ,NULL);}
else
{	wait(NULL);
	printf("PID= %d\n", pid);
 }

return 0;
}
