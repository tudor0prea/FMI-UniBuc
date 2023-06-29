#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem;
pthread_mutex_t mtx;
int viz = 0, nr_proc = 6;


void barrier_point(){
    viz+=1;
    pthread_mutex_lock(&mtx);
    if(viz==nr_proc){
        pthread_mutex_unlock(&mtx);
        sem_post(&sem);
        return;
    }
    
    pthread_mutex_unlock(&mtx);
    
    sem_wait(&sem);
    
    viz-=1;
    sem_post(&sem);
}


void *tfun(void *v){
    int *tid = (int*)v;
    printf("%d reached the barrier\n", *tid);
    barrier_point();
    printf("%d passed the barrier\n", *tid);
    
    free(tid);

    return NULL;
}

int main(){
    sem_init(&sem, 0, 0);
    pthread_mutex_init(&mtx, NULL);
    
    pthread_t* threads = malloc(sizeof(pthread_t) * nr_proc);
    
    for (int i=0; i<nr_proc;i++) {
        int* arg = malloc(sizeof(int));
        *arg = i;
        pthread_create(threads + i, NULL, tfun, arg);
    }
    
    for (int i = 0; i < nr_proc; i++)
        pthread_join(threads[i], NULL);
    free(threads);
    return 0;
}
