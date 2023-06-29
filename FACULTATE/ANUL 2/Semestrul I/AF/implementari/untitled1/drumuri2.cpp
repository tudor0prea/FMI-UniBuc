#include <iostream>
#include <vector>
using namespace std;
//MERGE -> relativ de explicat
// https://www.infoarena.ro/job_detail/2681459?action=view-source

//vrem sa det nr minim de drumuri ca sa acoperim graful

vector<vector<int>> a, b; //lista de adiacenta
vector<int> viz(500,0),
        parc(500,0), //daca am mai trecut sau nu prin nod
stg(500,0), dr(500,0);


int n, m;

bool cuplaj(int nod){

    if(parc[nod])
        //daca am mai fost prin acest nod
        return false;

    //altfel parcurgem lista de adiac a nodului
    //si formam muchii

    parc[nod]=1;

    for(auto i: b[nod])
        if(stg[i]==0)
        { // muchia este de forma i--->nod
            stg[i]=nod, dr[nod]=i;
            return true;}

    //daca nu, verificam in cuplaj in continuare
    for(auto i: b[nod])
        if(cuplaj( stg[i] )==true)
            // muchia este de forma i--->nod
        { dr[nod]=i, stg[i]=nod;
            return true;}

    return false;

}

void dfs(int nod) {
    viz[nod]=1;
    for(auto i: a[nod])
        if(!viz[i]) dfs(i);
}



int main() {
    int u, v;
    cin>>n>>m;

    a=vector<vector<int>>(n+1,vector<int>());
    b=vector<vector<int>>(n+1,vector<int>());

    for(int i=1;i<=m;i++)
    {
        cin>>u>>v;
        a[u].push_back(v);
    }


    for(int i=1;i<=n;i++)
    {


        for(auto i: viz)
            viz[i]=0;

        //facem o parcurgere prin acest nod
        dfs(i);

        for(int j=1;j<=n;j++)
            if(viz[j]!=0)
            {
                if(i!=j) b[i].push_back(j);
            }

    }

    //initializam vectorul parc cu zero
    for(auto i: parc)
        parc[i]=0;

    bool ok=true;
    while(ok) {

        ok=false;
        for(int i=1;i<=n;i++)
            if(!dr[i]) {
                if(cuplaj(i))
                    ok=1;
                else ok=0;
                //ok|=cuplaj(i);

            }

        //vect parc se va initializa de fiecare data
        //ca sa pornim cu 0;
        for(auto i: parc)
            parc[i]=0;
    }

    int maxim=0;
    for(int i=1;i<=n;i++)
        if(dr[i]!=0)
            maxim++;

    cout<<n-maxim;

    return 0;
}