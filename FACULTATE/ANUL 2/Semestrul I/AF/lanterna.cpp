#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAXN 60
#define MAXK 1005
#define oo 1000000000
// nu merge inca
//https://www.infoarena.ro/job_detail/2939992?action=view-source
struct muchie { int destinatie, t, w; };

vector<muchie> vect[MAXN];
queue<pair<int,int>> coada; //nod,w
int incoada[MAXN][MAXK];
int n, m, k, bazamilitara[MAXN], distante[MAXN][MAXK];



int cost(int capacitate, int destinatie){
    int i,j;

    for(i=1;i<=capacitate;i++)
      for(j=1;j<=capacitate;j++)
        distante[i][j]=oo,incoada[i][j]=0;

    distante[1][capacitate] = 0 ;

    coada.push(make_pair(1,capacitate));

    incoada[1][capacitate] = 1;


    while(!coada.empty())
    {
        int n,w;
        n=coada.front().first;
        w=coada.front().second;
        coada.pop(); incoada[n][w]=0;

        for( auto &i: vect[n])
        {
            if(w>i.w)   //avem destui w pentru a merge mai departe
            {
                int capacitatenoua=w-i.w;
                if(bazamilitara[i.destinatie])
                    capacitatenoua=capacitate;
                if(distante[i.destinatie][capacitatenoua] > distante[n][w]+i.t)
                    //dist e mai scurta, deci o modificam
                {
                    distante[i.destinatie][capacitatenoua] = distante[n][w]+i.t;

                    if(!incoada[i.destinatie][capacitate])
                    {
                        coada.push(make_pair(i.destinatie,capacitatenoua));
                        incoada[i.destinatie][capacitatenoua]=1;
                    }

                }
            }

        }
    }

    int mini = oo;
    for(i=0;i<capacitate;i++)
        if(distante[destinatie][i] < mini)
            mini=distante[destinatie][i];

    return mini;
}

int main() {
    int i,a,b,t,w;
    muchie muchia;
    freopen("lanterna.in","r",stdin);
    freopen("lanterna.out","w",stdout);

    scanf("%d %d", &n, &k);

    for(i=1;i<=n;i++)
        scanf("%d",&bazamilitara[i]);

    scanf("%d",&m);

    //graf:
    for(i=1;i<=m;i++) {
        scanf("%d %d %d %d", &a, &b, &t, &w);
        muchia.destinatie=b;
        muchia.t=t;
        muchia.w=w;

        vect[a].push_back(muchia);

        muchia.destinatie=a;
        vect[b].push_back(muchia);
    }


    int tmin=cost(k,n);

    //cautare binara pentru costul minim

    int l=1,r=k;
    while(l<r){
        int mij=(l+r)/2;
        int t=cost(mij,n);
        if(t<=tmin)
            r=mij-1;
        else
            l=mij+1;
    }

    printf("%d %d ",l,tmin);

    return 0;
}