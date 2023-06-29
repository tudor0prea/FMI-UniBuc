#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 //MERGE - punctul a


 // alg lui Edmonds Karp

int n, m, nod, d;
vector<vector<int>> G;
int tata[500], cost[500][500];
int viz[500];

bool parcurgereBFS() {

    queue<int> coada;
    coada.push(nod);


    for(int i=1;i<=n;i++)
        viz[i]=0;

    viz[nod]=1; tata[nod]=-1;

    while(!coada.empty())
    {
        int top=coada.front();
        coada.pop();
        //scoatem primul nod din coada
        for(auto i: G[top])
            if(viz[i]==0)   //mergem prin nodurile adiacente cu top
                if(cost[top][i]!=0) {
                    tata[i] = top;
                    if(i==d) //daca am ajuns la destinatie
                        return true;

                    viz[i]=1; coada.push(i);
                }
    }

    return false;
}


void parcurgereDFS(int nod) {
    viz[nod]=1;
    for(int i=1;i<=n;i++)
        if(cost[nod][i]!=0 && viz[i]==0)
            parcurgereDFS(i);
}


int main(){
    int fmax=0;

    cin>>n>>m;
    G.resize(n+1);

    for(int i=1;i<=m;i++)
    {
        int destinatie,sursa,capacitate;
        cin>>destinatie>>sursa>>capacitate;
        G[destinatie].push_back(sursa);
        G[sursa].push_back(destinatie);

        cost[destinatie][sursa]=capacitate;
    }
    nod=1; d=n; //de unde plecam si pana unde mergem
    while(parcurgereBFS()){
        int a,b;
        b=nod;

        int fluxCurent=9999;

        for(int i=d;i!=nod;i=tata[i])
            if(cost[tata[i]][i] < fluxCurent)
                fluxCurent=cost[tata[i]][i];

        for(int i=d;i!=nod;i=tata[i])
            cost[tata[i]][i] = cost[tata[i]][i] - fluxCurent,
            cost[i][tata[i]] = cost[i][tata[i]] + fluxCurent;

        fmax=fmax+fluxCurent;
    }

    cout<<fmax;


    return 0;
}