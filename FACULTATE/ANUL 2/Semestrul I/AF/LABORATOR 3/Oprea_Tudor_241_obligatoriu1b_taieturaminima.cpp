#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// punctul b
//am luat algoritmul de la zero
//pentru a determina taietura minima cu ajutorul
//unui graf rezidual (FordFulkerson)

//explicatii si idee de pe geeksforgeeks

#define n 7



int bfs( int rG[n+1][n+1], int nod, int d,int tata[]){

    int viz[n+1];
    for(int i=1;i<=n;i++)
        viz[i]=0;


    queue<int> coada; coada.push(nod);
    viz[nod]=1;
    tata[nod]=-1;

    while(!coada.empty())
    {
        int top=coada.front(); coada.pop();

        for(int i=1;i<=n;i++)
            if(viz[i]==0)
                if(rG[top][i]>0)
                {
                    coada.push(i); tata[i]=top;
                    viz[i]=1;
                }
    }
    return (viz[d] == 1); //daca am ajuns la destinatie, returnam 1
}

void parcurgereDFS(int rG[n+1][n+1],int nod, int viz[]) {
    viz[nod]=1;
    for(int i=1;i<=n;i++)
        if(rG[nod][i]!=0)
            if(viz[i]==0)
                parcurgereDFS(rG,i,viz);
}



int main(){
    int G[n+1][n+1], m;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            G[i][j]=0;

    //am pastrat graful ca pe o matrice de adiacenta
    //care sa contina si capacitatea fiecarei muchii

    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int destinatie,sursa,capacitate;
        cin>>destinatie>>sursa>>capacitate;

        G[destinatie][sursa]=capacitate;
    }


    for(int i=1;i<=n;i++)
    {for(int j=1;j<=n;j++)
            cout<<G[i][j]<<" ";
        cout<<endl; }




    int nod=1; int d=6;

    //ne facem un graf rezidual
    int rG[n+1][n+1];

    //graful rezidual il copiaza pe cel initial
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            rG[i][j]=G[i][j];

    int tata[n+1];

    while( bfs(rG, nod,d,tata)){

        int fmax=9999;

        for(int i=d;i!=nod;i=tata[i])
            if(fmax > rG[tata[i]][i])
                fmax=rG[tata[i]][i];

        for(int i=d;i!=nod;i=tata[i])
            rG[tata[i]][i] -= fmax,
                    rG[i][tata[i]] +=fmax;
    }

    //am det fluxul, acum taietura
    int viz[n+1];

    for(int i=1;i<=n;i++)
        viz[i]=0;

    parcurgereDFS(rG,nod,viz);

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if( viz[i]!=0 && viz[j]==0)
                if(G[i][j]!=0)
                    cout<<i<<" "<<j<<endl;
    return 0;
}
/* exemplu: //daca avem n(7) noduri si 10 muchii
10
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