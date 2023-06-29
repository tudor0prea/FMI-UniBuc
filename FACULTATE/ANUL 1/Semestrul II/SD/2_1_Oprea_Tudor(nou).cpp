#include <iostream>
using namespace std;

void MinHeap(int *v, int a, int n)
{
   int i=a, tata, varf, ok=0;
   tata= v[a];
   varf=tata;
         
   if(tata>v[2*a+1] && v[2*a+2]>v[2*a+1])     
         {swap(v[a],v[2*a+1]); ok=1;}
   if( tata>v[2*a+2] && v[2*a+2]<v[2*a+1])
         swap(v[a],v[2*a+2]) , ok=1;
   
   if(ok==1)
      MinHeap(v, i, n);
      
}
void Construire(int *v, int n) 
{
   int i;
   for(i= n/2-1; i >= 0; i--) 
      MinHeap(v, i, n);
   
}


void Decapitare(int *v, int &n)

{  int i,j;
  
  for(i=n-1; i >= 3 ; i--)
   {swap(v[0],v[i]);
   for(j=0;j<n;j++)
       cout<<v[j]<<"* ";
       cout<<endl;
   MinHeap(v, 0, i);
       for(j=0;j<n;j++)
       cout<<v[j]<<" ";
       cout<<endl;
   }
    
  
  n--;
  return;
}


int main() 
{
   int n, i;
   
   cin>>n;
   int v[30];
   for (i = 0; i <n; i++) 
      cin>>v[i];
      
   Construire(v, n);
   for( i=0;i<n;i++)
   cout<<v[i]<<" ";
   cout<<endl;
   
     
   Decapitare(v,n);
  
   for (i = 0; i < n; i++) 
      cout<<v[i]<<endl;
   
   return 0;
} 