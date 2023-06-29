#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *reverse(void *a) {
	char *cuvant = (char*) a;
	char *inv= (char*)malloc(strlen(cuvant));
	int j=0;
	for(int i=strlen(cuvant)-1;i>=0;i--)
		{inv[j]=cuvant[i];
		j=j+1;
		
		}
	
	printf("%s", inv);
	return NULL; 
	}
	
int main (int argc, char *a[]) {

	pthread_t thr ;
	if ( pthread_create (& thr , NULL , reverse , a[1])) {
		perror ( NULL );
	return errno ;
	}

	pthread_join (thr , NULL );
	
	printf("\n");
	
	return 0;
	}
