#include <fstream>
#include <vector>
#include <set>
#include <queue>
#define MAXI 100001
using namespace std;
//VARIANTA ASTA MERGE!

struct Drum{
    int destinatie, distanta;
};

struct Catun{
    int cetate, dmin; //distanta minima
}c[10000];

vector<Drum> G[10000];
queue<int> coada;
int viz[10000];



void Dijkstra() {
    while(!coada.empty())
    {
        int x = coada.front();
        viz[x]=0; coada.pop();

        for(int i=0;i<=G[x].size();i++) {

            int d = G[x][i].distanta;
            int dest = G[x][i].destinatie;

            if (c[dest].dmin > c[x].dmin + d)
            {
                //inseamna ca am gasit o distanta mai scurta
                //   pana la o cetate
                c[dest].dmin = c[x].dmin + d;
                c[dest].cetate = c[x].cetate;

                if(!viz[dest])
                    viz[dest] = 1, coada.push(dest);
            }
            else
                if (c[dest].dmin== c[x].dmin + d)
                    // inseamna ca am gasit o cetate cu aceeasi distanta,
                    //     asa ca o sa comparam indicele cetatii
                    if(c[dest].cetate > c[x].cetate)
                    {
                        c[dest].cetate = c[x].cetate;

                        if(!viz[dest])
                            viz[dest]=1, coada.push(dest);
                    }

        }
    }
}


int main() {
    int i, n, m, k, a, b, dist;
    set<int> multime; // multimea tuturor cetatilor

    freopen("catun.in","r",stdin);
    freopen("catun.out","w",stdout);

    scanf("%d %d %d", &n, &m, &k);

    for(i=1;i<=n;i++)
        c[i].cetate=0, c[i].dmin=MAXI;

    // citim cetatile
    for(i=1;i<=k;i++){
        scanf("%d",&a);
        c[a].dmin = 0;
        c[a].cetate = a;
        viz[a]=1;
        coada.push(a);
        multime.insert(a);
    }

    for(i=1;i<=m;i++){
        scanf("%d %d %d", &a, &b, &dist);

        Drum d;
        d.distanta = dist;

        d.destinatie = b;
        G[a].push_back(d);

        d.destinatie = a;
        G[b].push_back(d);
    }

    Dijkstra();

    for(i=1;i<=n;i++)
        if(multime.find(i) != multime.end())
            printf("0 ");
        else
            printf("%d ", c[i].cetate);

    return 0;
}