#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define NMax5 50005
#define inf 9999
using namespace std;

ifstream f("graf.in");
int n, m, k, r;
vector<vector<int>> a; //matricea de adiacenta
int costuri[100][100], surse[100], destinatii[100];


vector<int> Dijkstra(int s)
{
    priority_queue <pair<int,int>> q;   // coada cu prioritati {cost,nod}
    bool vizDij[NMax5] = {0};     // viz[x] = 1 daca nodul a fost vizitat
    int dist[NMax5];        // dist[x] = distanta de la nodul de start la nodul x
    vector <int> Sol;

    // initial presupunem fiecare dist ca fiind infinit
    for(int i = 1; i <= n; ++i)
        dist[i] = inf;

    q.push({0,s});  // adaugam in coada nodul de inceput cu costul 0 (de la s la s avem distanta 0)
    vizDij[s] = 1;  // marcam nodul ca fiind vizitat
    dist[s] = 0;    // distanta de la s la s va fi 0

    while(!q.empty())
    {
        int nod_curent = q.top().second; // nodul curent
        q.pop();

        vizDij[nod_curent] = 0; // presupunem ca nodul curent nu a fost vizitat inca

        for(auto i : muchii[nod_curent])  // parcurgem nodurile adiacente cu nodul curent
        {
            int y = i.second;      // nodul adiacent cu nodul curent
            int cost = i.first;    // costul de la nodul curent  pana la y

            if(dist[nod_curent] + cost < dist[y])
            {
                dist[y] = dist[nod_curent] + cost;
                if(!vizDij[y]) // marcam nodul ca fiind vizitat daca nu era
                {
                    vizDij[y] = 1;
                    q.push({dist[y],y}); // adaugam din nou in coada pt ce ne ar putea imbunatati costul ulterior
                }
            }
        }
    }

    for(int i = 2; i <= n; ++i)
    {
        if(dist[i] != inf)
            Sol.push_back(dist[i]);
        else
            Sol.push_back(0);
    }

    return Sol;
}


int main() {
    f>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int dest, sursa, cost;
        f>>sursa>>dest>>cost;
        a[sursa].push_back(dest);
        a[dest].push_back(sursa);
        costuri[sursa][dest]=cost;
    }

    f>>k;
    for(int i=1;i<=k;i++)
        f>>surse[i];
    f>>r;
    for(int i=1;i<=r;i++)
        f>>destinatii[i];


    int mini=inf;

    for(int i=1;i<=k;i++)
        for(int j=1;j<=r;j++)
            //if()
                return 0;
}
