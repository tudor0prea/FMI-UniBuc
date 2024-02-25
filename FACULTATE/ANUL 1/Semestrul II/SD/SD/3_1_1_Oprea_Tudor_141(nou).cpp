#include <iostream>
using namespace std;

int main()
{ int A[1000]={1, 2, 6, 7 ,10, 12, 30}, B[500]={3, 5 ,8, 11, 29}, n=7, m=5;


int indice=m+n, x=n-1, y=m-1, i;

for(i=m+n-2; i>0 && x>0 && y>0 ;i--)
   if (A[x]>B[y])
     { A[i]=A[x];
     x--;}
    else 
    { A[i]=B[y];
     y--; }

while (y>0)
{ A[i]=B[y];
y--;
i--;
}


for(int i=0;i<m+n-1;i++)
 cout<<A[i]<<" ";

   
return 0; }