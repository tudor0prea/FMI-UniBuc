#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int n,m;
vector<int> tata(999), lista(999);
map< int, vector<pair<int, int>> > a;
ifstream f("dbz.in"); ofstream g("dbz.out");


void algDijkstra (int s) {

    priority_queue < pair<int,int>,
                     vector<pair<int,int> >,
                     greater <pair <int,int>> > q;

    for(int i=1;i<=n;i++) {
        tata[i] = 0;
        lista[i]=999;
    }

    lista[s]=0;

    for(auto i : a[s])
    {
        q.push( make_pair (i.second, i.first));
        lista[i.first]=i.second;
        tata[i.first]=i.first;
    }

    while(q.size()) {
        auto top = q.top();

        q.pop();

        int pct = top.second;
        int dist = top.first;

        if (dist > lista[pct])
            continue;

        for (auto j: a[pct])
            if (lista[j.first] > lista[pct] + j.second) {
                lista[j.first] = lista[pct] + j.second;
                q.push(make_pair(lista[j.first], j.first));
                tata[j.first] = tata[pct];
            }
    }
    int mini=9999;

    for(int i=1;i<=n;i++)
        for(auto j: a[i]) {
            if(tata[i] != tata[j.first]
                && (tata[i]!=i || j.first!=s) &&
                (tata[j.first]!=j.first || i!=s) )
                   if(lista[i] + lista[j.first]+j.second < mini)
                       mini=lista[i] + lista[j.first]+j.second;

            }
        if(mini == 9999) g<<-1<<" ";
        else g<<mini<<" ";
    }


int main() {
    f>>n>>m;

    for(int i=1;i<=m;i++)
    {
        int x, y, z;
        f>>x>>y>>z;
        a[x].push_back(make_pair(y,z));
        a[y].push_back(make_pair(x,z));

    }


    for(int i=1;i<=n;i++)
        algDijkstra(i);
        g<<endl;

    return 0;
}

