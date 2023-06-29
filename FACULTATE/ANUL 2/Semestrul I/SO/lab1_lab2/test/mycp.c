#include <unistd.h>
#include <fcntl.h>
 

int main(int nrarg,char *y[]) {

    char mesaj[30];
     
     int z=open(y[1], O_RDWR);
    
    read(z,mesaj,sizeof(mesaj));
    
    int t=open(y[2], O_WRONLY);
    
    write(t,mesaj,sizeof(mesaj));
    
    
    
    return 0;}
    
