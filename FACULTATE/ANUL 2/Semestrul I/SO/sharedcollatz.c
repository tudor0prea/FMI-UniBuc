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
    // daca nu sunt destule argumente
    
    // argc-1  pentru ca ex1.c este luam si el in considerare in argc => o sa fie argc-1 numere pt collatz 
    pid_t pids[argc-1];	// vector de procese = nr argumente;
 
    
    
    // zona de memorie totala
    size_t shm_size = getpagesize()*(argc-1);	// o zona de memorie mare care are nr_argumente * unitate  ( getpagesize() = o unitate )
    
    int x, len, i, j;
    
    printf("Starting parent %d\n", getppid());
    
    char shm_name[] = "zona_de_memorie_comuna";	// am pus nume mai sugestiv
    char shm_name_indexi[] = "zona_de_memorie_comuna_pt_lungimi"; 
    // in fiecare proces copil trebuie sa aflu lungimea pt collatz(nr_respectiv)
    // procesele copil nu modifica memoria din parinte, nici invers
    // din cauza asta, am nevoie de o zona de memorie care sa fie vazuta de procesul principal, in care sa stochez acele valori
    
    
    int shm_fd_indexi;
    int shm_fd; // descriptorul pt zona de memorie, acesta e foarte important, deoarece prin el accesam zona de memorie
    // acesta o sa reprezinte un pointer catre zona de memorie
    
    shm_fd_indexi = shm_open(shm_name_indexi, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd_indexi < 0) {perror(NULL); return errno; }
    
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);	// am luat un descriptor care arata catre zona aia de memorie
    if(shm_fd < 0) {perror(NULL); return errno; }
    
    
    // e de ajuns sa aloc getpagesize() / sizeof(int)  locuri (1024 daca pagesize = 4096)
    if(ftruncate(shm_fd_indexi, getpagesize() ) == -1)  
    {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
    
    // schimb marimea zonei de memorie comuna la size-ul total
    if(ftruncate(shm_fd, shm_size)==-1){
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }
     
     

    for(i=0;i<argc-1;++i)
        if( (pids[i]=fork() ) <0)		// creare proces copil 
            return errno;
        else if(pids[i]==0)
        {
        	int aux;
   
        	// pointer-ul acesta va incepe de la pozitia unitate * i   (unitate = getpagesize() )
            	int* shm_ptr = mmap(0,getpagesize(), PROT_WRITE, MAP_SHARED, shm_fd, getpagesize()*i);
            	if(shm_ptr == MAP_FAILED){
                	perror(NULL);
                	shm_unlink(shm_name);
                	return errno;
            		}
		x = atoi(argv[i+1]);
            	aux = collatz(shm_ptr, x, 0);
            	
            	// deschid un pointer catre zona de memoria in care stochez indexii, incep de la offset byte = 0
            	int* shm_ptr_indexi = mmap(0,getpagesize(), PROT_WRITE, MAP_SHARED, shm_fd_indexi, 0);
            	shm_ptr_indexi[i] = aux; // pt procesul i , in zona de memorie pt indexi, pe pozitia i voi avea lungimea de afisare
            	
            	// dezaloc indexii ca nu mai am nev de ei
            	munmap(shm_ptr_indexi, getpagesize());
            	munmap(shm_ptr, getpagesize());
            	printf("Done Parent %d Me %d\n", getppid(), getpid());
            	exit(0); // inchei procesul copil
        }
        
    for(i=0;i<argc-1;++i){
         
        wait(NULL);
    }
    
    // dupa ce am asteptat pt toate procesele copil sa se termine, urmeaza sa fac afisarea din zona de memorie comuna
    
   
    int *zona_indexi = mmap(0,shm_size, PROT_READ, MAP_SHARED, shm_fd_indexi, 0);
    int *zona_totala = mmap(0,shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    // deschid ca un vector de int zona respectiva de memorie, pt citire (PROT_READ) , de la offset 0  
    int lungime;
    int offset;
    
    
    for(i=0;i<argc-1;i++)
    {
    	lungime = zona_indexi[i];   // iau cate pozitii s-au facut pt fiecare nr 
    	offset = (getpagesize()/4)*i;	// din cauza ca am deschiz zona_totala ca int, trebuie sa am grija ca se vor lua cate 4 bytes pt un nr
    	// 
	// 	EXPLICATIE
	//
	
	// am o zona de memorie de 12 bytes
	// 0 1 2 3 4 5 6 7 8 9 10 11 
	
	// daca o deschid ca char (char are 1 singur byte), atunci voi avea 12 pozitii
	// daca o deschid ca int (int are 4 bytes) , atunci voi avea 12 bytes / 4 = 3 poziti
	// bytes 0 1 2 3   => pozitia 0
	// bytes 4 5 6 7   => pozitia 1
	// bytes 8 9 10 11 => pozitia 2
	
	// de aceea eu iau offset-ul ca getpagesize()/4
	
    	printf(" %d : ",zona_totala[offset]);	// afisez nr respectiv la care s-a facut collatz
    	for(j=0;j<lungime;j++)
    	{
    	   printf("%d ",zona_totala[offset+j]);			// afisez toata "evolutia" cum a ajuns la 1
    	}
    	printf("\n");
    }
    printf("Done Parent %d Me %d\n",getppid(),getpid());
    // nu mai folosesc deloc zonele de memorie, asa ca le sterg
    shm_unlink(shm_name);	
    shm_unlink(shm_name_indexi);		
    munmap(zona_totala,shm_size);
    munmap(0, getpagesize()*argc);
    
    return 0;
}
