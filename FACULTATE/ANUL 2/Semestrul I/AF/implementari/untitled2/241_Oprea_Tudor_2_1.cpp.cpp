#include <vector>
#include <set>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

int n, m, a[100][100];
vector<int> linii_nule, lista_leg;
ifstream f("graf.in");

int main() {
    f>>n>>m;

    for(int i=1;i<=m;i++) {
        int u, v;
        f>>u>>v;
        a[u][v]=1;
        a[v][u]=1;
    }

    int k=0;
    for(int i=1;i<=m;i++)
    {
        int zero=0;
        for(int j=1;j<=m;j++)
            if(a[i][j]==1 && a[j][i]==1)
                zero=1;
        if(zero==0)
        {
            //inseamna ca am gasit o linie doar cu zerouri
            linii_nule.push_back(i);
            k++;
        }
    }


    int count=0;

    for(int i=1;i<=m && count<k;i++)
    {
        int gasit=0;
        vector<int> lista_leg1;
        for(int j=1;j<=m;j++)
            //daca nodul nostru este legat de cel putin 2
            if(a[i][j]==1) {
                gasit++;
                lista_leg1.push_back(j);
            }
        if(gasit>=2)
        {
            count++;
            lista_leg.push_back(i);
        }

    }
    if(count<k)
        cout<<"nu se poate";
        else
        {
            cout<<"k="<<k<<"\n";
            cout<<"k-stergerea arcelor\n";
            for(auto a:lista_leg)
            cout<<lista_leg[a]<<endl;

            cout<<"k-adaugarea arcelor\n";
            for(auto a: linii_nule)
                cout<<linii_nule[a]<<endl;
        }
        return 0;

}