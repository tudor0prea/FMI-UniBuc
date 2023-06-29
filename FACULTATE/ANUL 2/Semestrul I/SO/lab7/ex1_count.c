#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#define MAXRESOURCES 5
#define MAXTHREADS 6
int available_resources = MAXRESOURCES;

pthread_mutex_t mtx;
int sz = MAXTHREADS;
int cnt_threads[MAXTHREADS] = {2,3,2,2,1,1};

int decrease_count(int count)
{
    
    
    if(count<=available_resources)
        available_resources -= count;
        
    else
       { while(available_resources<count);
        pthread_mutex_lock(&mtx);
    	available_resources -= count; }
    printf("Got %d resources, %d remaining\n", count, available_resources);
    return pthread_mutex_unlock(&mtx);
     
}

int increase_count(int count)
{
    
    if(available_resources+count<=MAXRESOURCES)
         available_resources += count;
         
    else
         {while(available_resources+count > MAXRESOURCES);
         pthread_mutex_lock(&mtx);
         available_resources+=count; }
         
         printf("Released %d resources, %d remaining\n", count, available_resources);
    
    return pthread_mutex_unlock(&mtx);
   
}

void* my_thread(void* x){
    int count = *((int*)x);
 
     decrease_count(count);
     //sleep(1);
     increase_count(count);
    return NULL;
}

int main(){
    
    if (pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno ;
    }

    printf("MAXRESOURCES=%d\n", MAXRESOURCES);
    pthread_t thr[sz]; 
    
    for(int i=0;i<sz;i++)
        pthread_create(&thr[i], NULL, my_thread, &cnt_threads[i]);
    for(int i=0;i<sz;i++)
        pthread_join(thr[i], NULL);

    pthread_mutex_destroy(&mtx);
    return 0;
}
