#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
 
int p;		// partea comuna dintre cele 2 matrici: mat1 = m*p , mat2 = p*n
 
int **mat1,**mat2; 
 
typedef struct dual
{
	int linie;
	int coloana;
} dual;
 
// pentru ca eu am DOAR UN PARAMETRU, acela de tip void, ca sa "simulez" mai multi parametri, ma folosesc de un struct
// asa ca pt functia LiniexColoana(int l1, int l2) am transformat-o in LiniexColoana(dual aux) , care contine linie(l1) si coloana(l2)
 
void* LiniexColoana (void* parametru)
{ 
	int i,j;
	int *s = malloc(sizeof(int));
	dual *aux = (dual*)parametru;		// ii dau cast de la void* la dual*
	// functia returneaza (void*) (adica pointer) de o valoare, asa ca m-am gandit s-o aloc in memorie 
	//ca sa nu fie stearsa daca era statica (nush cat de corect e)
 
	*s = 0;
	int l1,l2;
	l1 =(int) aux->linie;  // -> pt ca sunt pointeri, iau parametrii din aux
	l2 =(int) aux->coloana;
   	for(i=0;i<p;i++)	
   		*s+=mat1[l1][i]*mat2[i][l2];
 
   	return (void*)*s; 	
  } 		
 
 
int main(int argc, char** argv) {
 
	// argv[0] = numele executabilului
	int m = atoi(argv[1]);
	p = atoi(argv[2]);
	int n = atoi(argv[3]);
 
 
	int i,j;
	int **mat3;
 
	// aloc nr de randuri
	mat1 = (int**) malloc(m*sizeof(int*));
	mat2 = (int**) malloc(p*sizeof(int*));
	mat3 = (int**) malloc(m*sizeof(int*));
 
	// aloc nr de coloane pt fiecare rand
	for(i=0;i<m;i++)
		mat1[i] = (int*) malloc(p*sizeof(int*));
	for(i=0;i<p;i++)
		mat2[i] = (int*) malloc(n*sizeof(int*));
	for(i=0;i<m;i++)
		mat3[i] = (int*) malloc(n*sizeof(int*));
 
	int index = 3;	// incep de la 3 si incrementez imediat, ca sa fiu pe pozitia exacta in argv[]
 
	// citire elemente pt mat1, mat2
	for(i=0;i<m;i++)
		for(j=0;j<p;j++)
		{
			index++;
			mat1[i][j] = atoi(argv[index]);
			//printf("%d -> %d\n",index,atoi(argv[index]));
		}
	for(i=0;i<p;i++)
		for(j=0;j<n;j++)
		{
			index++;
			mat2[i][j] = atoi(argv[index]);
			//printf("%d -> %d\n",index,atoi(argv[index]));
		}
 
	int nr_elemente = m*n;	
	// nr de thread-uri  (cerinta zice sa avem un thread pt fiecare element din matrice)
 
	pthread_t threads[nr_elemente];		// threaduri
	int rez[nr_elemente];			// rezultatele aferente
	dual parametrii[nr_elemente];		// parametrul pt functia de apelat
 
 
	// !!! DIN CAUZA MEMORIEI, SA NU SE INTAMPLE VREO TAMPENIE, AM NEVOIE DE rez SI parametrii
	// 
	index = -1;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			// setez parametrul pt functie
			index++;
			parametrii[index].linie = i;	// linia mat3
			parametrii[index].coloana = j;	// coloana mat3
			if( pthread_create(&threads[index], NULL, LiniexColoana, &parametrii[index] ) )
			{
				perror(NULL);
				return errno;
			}
		}
 
	index = -1;
	for(i=0;i<m;i++)
	for(j=0;j<n;j++)
	{
		index++;
		// astept thread-ul index
		if( pthread_join (threads[index], &rez[index]) )	
			{
				perror(NULL);
				return errno;
			}
		// atribui valoarea din rez si afisez
		mat3[i][j] = rez[index];
		printf("mat3[%d][%d] = %d\n",i,j,mat3[i][j]);
	}	
 
 
 
	return 0; }
