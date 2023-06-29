#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

int collatz(int *vector, int x, int i){
    vector[i] = x;
    if(x==1) return i+1;
    
    else if(x%2==0) x=x/2;
    		else x=3*x+1;
    return collatz(vector, x, i+1);
}


int main(int argc, char **argv){
    
    if(argc<2) return -1;
    
    pid_t pids[argc];
    size_t shm_size = getpagesize()*argc;
    int x, len, i, j;
    
    
    
    printf("Starting parent %d\n", getppid());
    
    char shm_name[] = "fisier_comun";
    int shm_fd;
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd < 0) {perror(NULL); return errno; }
    
    if(ftruncate(shm_fd, shm_size)==-1){
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    for(i=0;i<argc;++i)
        if((pids[i]=fork())<0)
            return errno;
        else if(pids[i]==0)
        {
            	int* shm_ptr = mmap(0,getpagesize(), PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, getpagesize()*i);
            	if(shm_ptr == MAP_FAILED){
                	perror(NULL);
                	shm_unlink(shm_name);
                	return errno;
            		}
		x = atoi(argv[i+1]);
            	len = collatz(shm_ptr, x, 0);
            	//printf("%d: ", x); 
            
            	//for(j=0;j<len;++j)
                //	printf("%d ", shm_ptr[j]);
            	
            	//printf("\n");
            	exit(0);
        }
         
    for(i=0;i<argc;++i){
        printf("Done Parent %d Me %d\n", getppid(), getpid());
        wait(NULL);
    }
    //x = atoi(argv[i+1]);
    len = collatz(shm_ptr, x, 0);
    printf("%d: ", x); 
    for(i=0;i<argc;++i)
    	for(j=0;j<len;++j)
              printf("%d ", shm_ptr[j]);
       printf("\n");

    shm_unlink(shm_name);
    munmap(0, getpagesize()*argc);

    return 0;
}
