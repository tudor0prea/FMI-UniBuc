#include <iostream>
//#include <vector>
#include <queue>
#include <bits/stdc++.h>
// DA -: problema cu harta
//https://www.infoarena.ro/job_detail/2956833?action=view-source
using namespace std;
int viz[300], tata[300];
int a[300][300], intrare[300], iesire[300];

int m, n, x, flux, flmax;

//bfs pentru flux maxim cu 2n+1 in loc de t
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

        if(nod==2*n+1) return true;

        for(int i=1;i<=2*n+1;i++)
            if( viz[i]==0 && a[nod][i] >0)
            {
                coada.push(i); viz[i]=1;
                tata[i]=nod;
            }
    }
    return false;
}


int main(){
    cin>>n;

    for(int i=1;i<=n;i++) {
        cin>>iesire[i]>>intrare[i];

        a[0][i] = iesire[i];
        a[n+i][2*n+1]= intrare[i];

        for(int j=1;j<=n;j++)
            if(j!=i)
                a[i][n+j] = 1;
    }


    while( bfs() ) {
        for(int i=1;i<=n;i++)
            //daca a fost vizitat
            if(viz[n+i]==1)
                //daca a ajuns la dest
                if(a[n+i][2*n+1] >0){
                    flux= 99999;
                    tata[2*n+1]=n+i;
                    //mergem pe drumul de la t la s
                    // cautam cel mai mic iP
                    for(x=2*n+1;x!=0;x=tata[x])
                        //mergem din tata in tata
                        if(a[tata[x]][x] < flux)
                            flux=a[tata[x]][x];

                    if(!flux) continue;

                    for(x=2*n+1;x!=0;x=tata[x])
                        a[tata[x]][x]= a[tata[x]][x] - flux,
                                a[x][tata[x]]= a[x][tata[x]] + flux;

                    flmax=flmax+flux;


                }
    }

    cout<<flmax<<endl;

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j && a[i][n+j]==0)
                cout<<i<<" "<<j<<endl;

    return 0;
}
