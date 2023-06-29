#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
//MERGE! -> flux maxim
// https://www.infoarena.ro/job_detail/2958743?action=view-source

//Alg lui Ford Fulkerson

int n, m, s=1, d;  //sursa, destinatia

vector<vector <int>> la, li, cost, flux;  //lista de adiacenta, lista inversa
vector<int> viz, tata;


bool drum() {
    //initializam vectorii
    tata=vector<int>(n+1,0);
    viz=vector<int>(n+1,0);

    queue<int> coada;

    coada.push(s);
    viz[s]=1;
    while(!coada.empty()) {
        int x=coada.front(); //scoatem un nod din coada
        coada.pop();

        for(auto i: la[x]) //ii parcurgem lista de adiacenta
            if(viz[i] ==0 )
                if( cost[x][i] - flux[x][i] >0 ) // daca putem trece cu fluxul nostru
                {
                    coada.push(i);
                    viz[i]=1;

                    tata[i]=x;

                    if( i == d) // daca am ajuns la destinatie
                        return true;
                }

        //parcurgem si lista de adiacenta inversa
        for(auto i : li[x])
            if(viz[i]==0)
                if(flux[i][x] > 0) {
                    coada.push(i);
                    viz[i]=1;

                    tata[i]=-x;

                    if( i==d)
                        return true;
                }

    }
    return false;
}


ifstream f("maxflow.in");
ofstream g("maxflow.out");

int main() {
    int i, j, fmax=0;

   cin>>n>>m;

    d=n; //destinatia este n
    la=vector<vector<int>>(n+1,vector<int>());
    li=vector<vector<int>>(n+1,vector<int>());

    cost=vector<vector<int>>(n+1,vector<int>(n+1,0));
    flux=vector<vector<int>>(n+1,vector<int>(n+1,0));


    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            cost[i][j]=0,flux[i][j]=0;

    for(i=0;i<m;i++)
    {
        int destinatie,sursa,capacitate;
        cin>>destinatie>>sursa>>capacitate;
        la[destinatie].push_back(sursa);
        li[sursa].push_back(destinatie);
        cost[destinatie][sursa]=capacitate;
    }


    while(drum()==true) //cat timp se pot gasi drumuri de la s la t
    {
        int iP=10000000; //  i(P)
        int t=d;
        while(t!=s){
            if(tata[t] >=0){

                if(cost[tata[t]][t] - flux[tata[t]][t] < iP)
                    iP = cost[tata[t]][t] - flux[tata[t]][t] ;
                t = tata [t];
            }
            else
            {
                if(flux[t][-tata[t]] < iP)
                    iP= flux[t][-tata[t]];
                t = -tata[t];
            }
        }

        t=d;
        while( t!= s)
        {
            if(tata[t]>=0)
                flux[tata[t]][t] = flux[tata[t]][t] + iP, t=tata[t];
            else
                flux[t][-tata[t]] = flux[t][-tata[t]] - iP, t=-tata[t];

        }
        fmax += iP;

    }
//    g<<fmax;
//    g<<"\nsfarsit\n";
    cout<<fmax;
    return 0;
}
