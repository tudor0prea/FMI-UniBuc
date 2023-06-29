#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]) { 
    char text[] = "Hello World!\n";

    
    
    //write(1, text, sizeof(text)); //1 inseamna in consola
    
    
    
    int x=open( argv[1], O_RDONLY);
    //afisare adresa descriptor
    printf("%d\n%s\n", x, argv[1]);

   struct stat st;
   stat(argv[1],&st);
   
   int size= (int) st.st_size;
   
       
    
    //write(x, text, sizeof(text));
    
    char *mesaj=(char*)malloc(size);
    
    
    read(x,mesaj,size); close(x);
     
    int y=open(argv[2], O_CREAT, S_IRWXU);
    
    close(y);
    y=open(argv[2],O_RDWR);
    
    
    int check = write(y,mesaj,size);
    //printf("\n %d == %d --eroare %d",y,check,errno);
    

    close(y);
    return 0;
}



