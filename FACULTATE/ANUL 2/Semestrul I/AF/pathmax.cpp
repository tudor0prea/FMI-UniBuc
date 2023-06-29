#include <vector>
#include <set>
#include <stdio.h>
#include <iostream>
using namespace std;

//VARIANTA ASTA MERGE
double maxProbability(int n, vector<vector<int>>& edges,
                      vector<double>& succProb, int start, int end)
{
    double c;
    int i, a, b, m;
    m=edges.size();
    vector<vector <pair <int, double> > > vect(n);

    for(i=0;i<=m-1;i++){
        a=edges[i][0];
        b=edges[i][1];
        c=succProb[i];

        vect[a].push_back({b,c});
        vect[b].push_back({a,c});
    }

    //algoritmul lui Dijkstra
    vector<int> viz(n,0);
    vector<double> probability(n,0.0);
    set<pair<double,int>> s;

    s.insert({0,start});
    probability[start]=1.0;

    while(s.size()) //cat timp avem elemente in multime
    {
        auto nod = *s.begin(); //pastram primul nod intr o variabila
        s.erase(s.begin()); //il eliminam din multime

        viz[nod.second] = 1; //(chiar daca poate era deja vizitat)

        for (auto &i: vect[nod.second]) {
            if (probability[nod.second] * i.second > probability[i.first]) {
                probability[i.first] = probability[nod.second] * i.second;
                s.insert({1.0 - probability[i.first], i.first});
            }
        }
    }
    return probability[end];

}

int main() {
    int n=3;
    vector<vector<int>> edges = {{0,1},{1,2},{0,2}};

    vector<double> succProb= {0.5,0.5,0.3};
    int start=0;
    int end=2;

    cout<<maxProbability( n, edges, succProb, start, end);
    return 0;
}