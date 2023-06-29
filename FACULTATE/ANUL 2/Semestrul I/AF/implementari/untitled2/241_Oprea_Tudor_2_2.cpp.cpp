#include <vector>
#include <set>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;


ifstream f("graf.in");
int n, m, k, r, surse[999], destinatii[999];
vector<vector<int>> edges;
vector<int> costuri;


double maxProbability(int n, vector<vector<int>>& edges,
                      vector<int>& costuri, int start, int end)
{
    double c;
    int i, a, b, m;
    m=edges.size();
    vector<vector <pair <int, double> > > vect(n);

    for(i=0;i<=m-1;i++){
        a=edges[i][0];
        b=edges[i][1];
        c=costuri[i];

        vect[a].push_back({b,c});
        vect[b].push_back({a,c});
    }

    //algoritmul lui Dijkstra
    vector<int> viz(n,0);
    vector<double> probability(n,0.0);
    set<pair<double,int>> s;

    s.insert({0,start});
    probability[start]=0;

    while(s.size()) //cat timp avem elemente in multime
    {
        auto nod = *s.begin(); //pastram primul nod intr o variabila
        s.erase(s.begin()); //il eliminam din multime

        viz[nod.second] = 1;

        for (auto &i: vect[nod.second]) {
            if (probability[nod.second] + i.second > probability[i.first]) {
                probability[i.first] = probability[nod.second] + i.second;
                s.insert({ probability[i.first], i.first});
            }
        }
    }
    return probability[end];

}

int main() {

    f>>n>>m;
    int nr=1;
    for(int i=1;i<=m;i++)
    {
        int dest, sursa, cost;
        f>>sursa>>dest>>cost;
        edges[i]=vector<int>(sursa,dest);
        costuri[i]=cost;
    }

    f>>k;
    for(int i=1;i<=k;i++)
        f>>surse[i];
    f>>r;
    for(int i=1;i<=r;i++)
        f>>destinatii[i];

    int maxi=0;
    int u,v;
    for(int i=1;i<=k;i++)
        for(int j=1;j<=r;j++)
            if( maxProbability( n, edges, costuri, surse[i], destinatii[j]) < maxi) {
                maxi = maxProbability(n, edges, costuri, surse[i], destinatii[j]);
                u = surse[i], v = destinatii[j];
            }
    cout<<maxi<<endl;

    cout<<"Drumul\n";
    cout<<u<<" "<<v<<endl;

    return 0;
}