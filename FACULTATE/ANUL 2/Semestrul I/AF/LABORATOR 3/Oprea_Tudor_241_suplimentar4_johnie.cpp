#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
//


// asemanator cu pb eulerian
// dar graful e neorientat
//hieholzer

//dfs din nodurile cu grad impar


vector<vector<pair<int,int>>> a(100000);
unordered_map<int, vector<int>> rasp;
vector<int> viz(100000);

int n, m, nr;

void dfs(int nod) {
    while(a[nod].size()!=0) {
        auto urmator=a[nod].back();
        //din nod mergem printr un vecin
        a[nod].pop_back();



        if( viz[urmator.second] == 0 )
            //daca acel vecin nu a fost vizitat
            //il marcam drept vizitata si continuam
            //dfs ul prin el
            viz[urmator.second]=1, dfs(urmator.first);

    }

    if(nod == 0) nr++;
    else rasp[nr].push_back(nod);
}


int main(){
    int u, v;
    cin>>n>>m;

    for(int i=0;i<m;i++){
        cin>>u>>v;

        a[u].push_back(make_pair(v,i));
        a[v].push_back(make_pair(u,i));

    }

    for(int i=1;i<=n;i++){
        int dim=a[i].size();
        // daca nodul este adiacent cu un nr impar
        // de noduri, atunci il "legam" nodului
        // nostru 0, ca sa il aducem aproape de inceperea
        // parcurgerii dfs ului
        if(dim%2==1)
            a[i].push_back(make_pair(0,i+m)),
            a[0].push_back(make_pair(i,i+m));

    }

    //pornim o parcurgere dfs din 0, ca sa trecem
    // prin nodurile legate anterior de zero:
    dfs(0);

    nr--; cout<<nr;

    cout<<endl;
    for(int i=1;i<=nr;i++) {
        cout << rasp[i].size() << " ";
        for(int x : rasp [i])
            cout<<x<<" ";
        cout<<endl;
    }
    return 0;
}




