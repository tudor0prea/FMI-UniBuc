#include <iostream>
//#include <vector>
#include <queue>
#include <bits/stdc++.h>
// cuplaj implementat cu flux
using namespace std;
int viz[300], tata[300];
int a[300][300], intrare[300], iesire[300];

int m, n, e, u, v, x, flux, cuplaj;

//bfs pentru flux maxim cu m+n+1 in loc de t
bool bfs(){
    //initializam vectorii
    //tata=vector<int>(n+1,0);
    //viz=vector<int>(n+1,0);
    memset(tata, 0, 300);
    memset(viz, 0, 300);
    queue<int> coada;

    coada.push(0);
    tata[0]=-1;

    while(!coada.empty()){
        int nod;
        nod=coada.front(); coada.pop();

        if(nod==m+n+1) return true;

        for(int i=1;i<=m+n+1;i++)
            if( viz[i]==0 && a[nod][i] >0)
            {
                coada.push(i); viz[i]=1;
                tata[i]=nod;
            }
    }
    return false;
}


int main(){
    //citirea datelor
    cin>>n>>m>>e;

    for(int i=1;i<=e;i++) {
        cin >> u >> v;
        a[u][n+v]=1;
    }

    //construirea retelei
    for(int i=0;i<=n;i++)
        a[0][i]=1;

    for(int i=1;i<=m;i++)
        a[n+i][n+m+1]=1;





    while( bfs() ) {
        for(int i=1;i<= n+m+1 ;i++)
            //daca a fost vizitat
            if(viz[n+i]==1)
                //daca a ajuns la dest
                if(a[n+i][n+m+1] >0){
                    flux= 99999;
                    tata[2*n+1]=n+i;
                    //mergem pe drumul de la t la s
                    // cautam cel mai mic iP
                    for(x=n+m+1;x!=0;x=tata[x])
                        //mergem din tata in tata
                        if(a[tata[x]][x] < flux)
                            flux=a[tata[x]][x];

                    if(!flux) continue;

                    for(x=n+m+1;x!=0;x=tata[x])
                        a[tata[x]][x]= a[tata[x]][x] - flux,
                                a[x][tata[x]]= a[x][tata[x]] + flux;

                    cuplaj=cuplaj+1;


                }
    }

    cout<<cuplaj<<endl;

    for(int i=1;i<=n;i++)
        for(int j=n+1;j<=n+m;j++)
            if(a[j][i]==1)
                cout<<i<<" "<<j-n<<endl;

    return 0;
}

// 4
// 1 1
// 2 3
// 3 2
// 5 4
