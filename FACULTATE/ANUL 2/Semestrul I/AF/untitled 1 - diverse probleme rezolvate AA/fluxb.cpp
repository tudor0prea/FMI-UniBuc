
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//~MERGE - punctul b

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
        for(auto i: cost[top]) //MODIFICAT
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

//void taieturaMinima() {
//
//    for(int i=1;i<=n;i++)
//        for(int j=1;j<=n;j++)
//            rG[i][j]=G[i][j];
//    for(int i=1;i<=n;i++)
//        viz[i]=0;
//
//    parcurgereDFS(1);
//
//    for(int i=1;i<=n;i++)
//        for(int j=1;j<=n;j++)
//            if(viz[i] == 1 && viz[j] == 0 && G[i][j]!=0)
//                cout<<i<<" "<<j<<endl;
//
//}
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


    //folosim "cost" pe post de un graf rezidual
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cost[i][j]=G[i][j];

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

        //fmax=fmax+fluxCurent;
    }

    //cout<<fmax;

    //    taieturaMinima();
    for(int i=1;i<=n;i++) viz[i]=0;

    parcurgereDFS(1);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(viz[i]!=0 && viz[j]==0 && G[i][j]!=0)
                cout<<i<<" "<<j<<endl;


    return 0;
}


/* exemplu:
 6 10
1 2 16
1 3 13
2 3 10
2 4 12
3 2 4
3 5 14
4 3 9
4 6 20
5 4 7
5 6 4

 */














