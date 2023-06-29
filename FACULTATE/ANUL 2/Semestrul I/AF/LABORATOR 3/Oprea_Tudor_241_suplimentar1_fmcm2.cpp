#include <iostream>
//#include <bits/stdc++.h>
#include <vector>
#include <queue>
using namespace std;



//alg lui BellmanFord pentru a calcula distantele
//alg lui Dijkstra - fara muchii cu costuri <0

int mat[500][500], cost[500][500], cmin=0,flux;
int tata[500];
int BF[500]; //BellmanFord
int real[500], pozitiv[500];
vector< vector<int>> a(500);
priority_queue<
        pair<int,int>,
        vector< pair<int,int> >,
        greater < pair<int,int> >
        >  coadaD;
int n,m, nod, d;

void algBellmanFord() {
    queue<int> coada;
    vector<int> adaugat(500,0);

    for(int i=1;i<=n;i++)
        BF[i]=9999;
    //initializam tot vectorul cu o val mare

    coada.push(nod);
    adaugat[nod]=1; BF[nod]=0;

    while(!coada.empty()){
        int top=coada.front(); coada.pop(); adaugat[top]=0;
        //scoatem un nod din coada

        for(auto i: a[top]) {
            //mergem printre nodurile alaturate celui scos
            if(mat[top][i]!=0)
                if(BF[i] > BF[top] + cost[top][i])
                {
                    BF[i]=BF[top] + cost [top][i];
                    //daca i nu mai este deja in coada, il adaugam
                    if( adaugat[i]==0)
                        coada.push(i), adaugat[i]=1;
                }
        }
    }

}

bool algDijkstra() {

    for(int i=1;i<=n;i++)
        pozitiv[i]=9999;

    pozitiv[nod]=0; real[nod]=0;

    coadaD.push(make_pair(0,nod));

    while(coadaD.size()) {
        auto top= coadaD.top(); coadaD.pop();

        int x = top.second;

        if(pozitiv[x] == top.first)
            for(auto i: a[x])
                if(mat[x][i]>0 && pozitiv[i] > pozitiv[x] + cost[x][i] + BF[x] - BF[i]) {
                    pozitiv[i] = pozitiv[x] + cost[x][i] + BF[x] - BF[i];

                    coadaD.push(make_pair(pozitiv[i],i));
                    real[i]= real[x] + cost[x][i];
                    tata[i]=x;
                }

    }

    for(int i=1;i<=n;i++)
        BF[i]=real[i];

    if(pozitiv[d]==9999) return false;

    flux = 9999;

    for(int i=d; i!=nod; i=tata[i]) //mergem din tata in tata
        if(flux> mat[tata[i]][i])
            flux=mat[tata[i]][i];

    for(int i=d;i!=nod;i=tata[i])
        mat[tata[i]][i] = mat[tata[i]][i] - flux,
                mat[i][tata[i]] = mat[i][tata[i]] + flux;

    cmin=cmin + flux*real[d];
    return true;

}

int main () {
    int u,v, capacitate, costul;
    cin>>n>>m>>nod>>d;

    for(int i=1;i<=m;i++){
        cin>>u>>v>>capacitate>>costul;
        a[u].push_back(v);
        a[v].push_back(u);

        mat[u][v]=capacitate;
        cost[u][v]=costul;
        cost[v][u]=-costul;
    }
    algBellmanFord();

    while(algDijkstra());

    cout<<cmin;
    return 0;
}