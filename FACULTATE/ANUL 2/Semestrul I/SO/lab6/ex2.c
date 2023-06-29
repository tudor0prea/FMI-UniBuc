#include<stdio.h>
#include<pthread.h>


int mat1[L1][C1]= {
{1,2,3},
{4,5,6},
{7,8,9} }

int mat2[L2][C2]= {
{10,11,12,13},
{14,15,16,17},
{18,19,20,21}}



int LiniexColoana (int l1, int l2)
{ int i,j,s=0;
   for(i=1;i<=p;i++)
   	for(j=1;j<=p;j++)
   		s+=mat1[l1][j]*mat2[j][l2];
   		
   return s; } 		

void *ProdusMatrice(void *n, void *m, void *p, void *mat1, void *mat2)
{

    int sum, i, j, k;

    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            sum=0;
            for(k=0; k<p; k++)
                sum = sum + mat1[i][k] * mat2[k][j];
            mat3[i][j] = sum;
        }
    }
    
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
            printf("%d ", mat3[i][j]);
        printf("\n");
    }
     return NULL;
}


int main(int argc, char *argv[]) {

	int m = (int*)argv[0];
	int p = (int*)argv[1];
	int n = (int*)argv[2];
	
	int *mat1=(int*)malloc(m*p);
	int *mat2=(int*)malloc(p*n);
	int *mat3=(int*)malloc(m*n);
	int index=3;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=p;j++)
		{	int val=(int*)argv[index];
			mat1[i][j]=val;
			index++; }
	
	for(int i=0;i<=p;i++)
		for(int j=0;j<=n;j++)
		{	int val=(int*)argv[index];
			mat2[i][j]=val;
			index++; }
	return 0; }


