#include <iostream>
#include <vector>
#include <queue>

using namespace std;


//alg lui BellmanFord pentru a calcula distantele
//alg lui Dijkstra - fara muchii cu costuri <0

//vector<vector <int>> cost;
//int cost[500][500],mat[500][500];
vector<vector<int>> a,cost,mat;
vector<int> tata(500,0),pozitiv(500,0), real(500,0);
int n,m, nod, d, cmin, flux;
vector<int> BF(500, 9999);


void algBellmanFord() {
    vector<int> adaugat(500, 0);

    queue<int> coada;



    coada.push(nod);
    adaugat[nod] = 1;

    BF[nod] = 0;

    while (!coada.empty()) {
        int x = coada.front();
        coada.pop();

        adaugat[x] = 0;

        for (auto i: a[x])
            //cautam in nodurile adiacente cu x
        {
            if (a[x][i] != 0)
                if (BF[i] > BF[x] + cost[x][i]) {
                    BF[i] = BF[x] + cost[x][i];
                    if (adaugat[i] == 0)
                        coada.push(i), adaugat[i] = 1;
                }
        }
    }
}

bool algDijkstra() {
        for(auto i:pozitiv)
            pozitiv[i]=9999;

        pozitiv[nod]=0;
        real[nod]=0;

        priority_queue<
            pair<int,int>,
            vector< pair<int,int> >,
            greater < pair<int,int> >
            >  coadaD;

        coadaD.push(make_pair(0,nod));

        while(!coadaD.empty()) {
            auto top=coadaD.top(); coadaD.pop();

            int nr=top.second;
            if(pozitiv[nr] == top.first)
                for(auto i: a[nr])
                    if(a[nr][i] > 0)
                        if(pozitiv[i]>pozitiv[nr]+cost[nr][i] + BF[nr]-BF[i])
                        {
                            pozitiv[i]=pozitiv[nr]+cost[nr][i] + BF[nr]-BF[i];
                            coadaD.push(make_pair(pozitiv[i],i));

                            real[i]=real[nr] + cost[nr][i];
                            tata[i]=nr;
                        }

        }

        for(int i=1;i<=n;i++)
            BF[i]=real[i];

        if(pozitiv[d]==9999)
            return false;

        flux = 9999;

        for(int i=d;i!=nod; i=tata[i])
            if(mat[tata[i]][i] < flux)
                flux=mat[tata[i]][i];

        for(int i=d;i!=nod; i=tata[i])
            mat[tata[i]][i] = mat[tata[i]][i] - flux,
            mat[i][tata[i]] = mat[tata[i]][i] + flux;

        cmin= cmin + flux*real[d];
        return true;
}


int main() {
    int u,v, capacitate, costul;

    cin>> n>> m;

    a=vector<vector<int>>(n+1,vector<int>());
    mat=vector<vector<int>>(n+1,vector<int>());
    cost=vector<vector<int>> (n+1,vector<int>());

    cin>>nod>>d;

    for(int i=0;i<m;i++){
        cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
        cin>>capacitate>>costul;
        mat[u][v]=capacitate;
        cost[u][v]=costul;
        cost[v][u]=costul;
    }

    algBellmanFord();

    while(algDijkstra());

    cout<<cmin;
    return 0;
}
