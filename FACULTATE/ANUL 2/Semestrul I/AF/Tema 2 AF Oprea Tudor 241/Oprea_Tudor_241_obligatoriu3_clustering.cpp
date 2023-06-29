#include <iostream>
#include <vector>
#include<fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

ifstream fin("clustering.in");
ofstream fout("clustering.out");

vector<string> cuv;
vector <int> tati;
vector <int> h;


void MatriceDistanta(char a[], char b[]){
    int i,j;
    int n=strlen(a);
    int m=strlen(b);
    int c[1000][1000]={0};

    for(i=0;i<=n;i++) c[i][0]=i;
    for(i=0;i<=m;i++) c[0][i]=i;

    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(a[i+1]==b[i+1])
                c[i][j]=c[i-1][j-1];
            else
                c[i][j]=1+min(c[i-1][j], min(c[i-1][j-1],c[i][j-1]));
    for(i=0;i<=n;i++)
    {for(j=0;j<=m;j++)
        cout<<c[i][j]<<" ";
        cout<<endl;}
    //return c[n][m];

}

int GasesteTata (int x) {
    if(tati[x]==0)
        return x;
    else
        x= GasesteTata(tati[x]);

    return tati[x];
}


int main(){
    char a[200],b[200];
    cin>>a>>b;
    cout<<MatriceDistanta(a,b);   //am verificat matricea de distante


//char c[20];
//while(fin>>c)
//    cuv.push_back(c);
//
//int dim = cuv.size();

 //dist dintre fiecare cuvant
//int i,j,d;
// for( i=0;i<dim;i++)
//    for( j=i+1; j<dim; j++) {
//        d = MatriceDistanta(cuv[i], cuv[j]);
//        muchii.push_back((i,j,d));
//
//    }



    return 0;
}