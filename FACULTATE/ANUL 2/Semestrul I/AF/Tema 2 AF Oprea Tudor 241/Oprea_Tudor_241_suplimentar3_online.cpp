#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int m, n, k, cost=0;
struct Drum { int destinatie, sursa, cost; }d;


vector <Drum> vect,G;
vector <int> tati;
vector <int> h;

bool ComparareOferte (Drum &d1, Drum &d2) {
    return d1.cost < d2.cost;
};

int GasesteTata(int x) {
    if(tati[x]!=x)
        tati[x]=GasesteTata(tati[x]);
    return tati[x];
}

void UnionFind(int x, int y){
    int p,q;

    p = GasesteTata(x);
    q = GasesteTata(y);

    if( p!=q )
        if( h[p] > h[q])
            tati[q] = p;
        else
        { tati[p] = q;
            if(h[p]==h[q]) h[p]+=1; }
}

void OferteInitiale (){
    sort(vect.begin(), vect.end(), ComparareOferte);
    for(int i=0;i< m ; i++)
    {
        int tata1 = GasesteTata(vect[i].destinatie);
        int tata2 = GasesteTata(vect[i].sursa);

        if(tata1 != tata2)
        {
            UnionFind(tata1, tata2);
            cost = cost + vect[i].cost;

            G.push_back(vect[i]);
        }
    }

    printf("%d\n", cost); // primul cost al lucrarii

    vect=G; G.clear();
}


int main() {

    freopen("online.in","r",stdin);
    freopen("online.out","w",stdout);

//citim datele initiale
    scanf("%d %d", &n, &m);

    for(int i=0;i<=n;i++)
        tati.push_back(i), h.push_back(0);

    for(int i=0;i<m;i++) {
        scanf("%d %d %d", &d.destinatie, &d.sursa, &d.cost);
        vect.push_back(d);
    }

    // costul initial, cu primele proiecte

    OferteInitiale();



    //Acum evaluam noile oferte (cele k)

    scanf("%d",&k);
    m = n;

    for(int i=0;i<k;i++)
    {
        cost=0, tati.clear(), h.clear();

        for(int j = 0 ; j<=n; j++)
            tati.push_back(j), h.push_back(0);

        //citim noua oferta

        scanf("%d %d %d",&d.destinatie,&d.sursa, &d.cost);

        vect.push_back(d);
        //facem exact ce am facut si prima data, doar ca includem si oferta noua

        OferteInitiale();

    }



    return 0;
}