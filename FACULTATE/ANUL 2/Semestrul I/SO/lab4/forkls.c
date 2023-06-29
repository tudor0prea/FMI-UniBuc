#include <sys/types.h>
#include  <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int  main() {
printf("My PID=%d , Child PID=%d\n", getppid(),getpid());
pid_t pid = fork ();


if ( pid < 0 ) 
	{ printf("Eroare\n"); return 0; }
else if ( pid == 0 )
	{//char *argv[]={"ls",NULL};
	execlp("ls", "ls" ,NULL);}
else
{	wait(NULL);
	printf("Child %d finished\n", getpid());
 }

return 0;
}
