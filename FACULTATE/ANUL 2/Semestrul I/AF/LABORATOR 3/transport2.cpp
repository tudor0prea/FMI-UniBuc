#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;


int n, m, cap_max;
vector<vector<pair<int,int>>> mat(9999);
int tata[9999], viz[9999];


int bfs(int cap_max){
    queue<int> q;

    for(int i=1;i<=n;i++)
        viz[i]=0;

    q.push(1); viz[1]=1;
    while(!q.empty()) {
        int top = q.front();
        q.pop();

        if (top == n)
            return 1;


        for (auto i: mat[top])
            if (viz[i.first] == 0 && i.second >= cap_max)
                q.push(i.first), viz[i.first]=1;
    }

    return 0;
}


int main() {
    int destinatie, sursa, capacitate, maxim=0;

    ifstream f("transport2.in");
    ofstream g("transport2.out");
    f>>n>>m;

    for(int i=1;i<=m;i++)
    {
        f>>destinatie;
        f>>sursa;
        f>>capacitate; //masa maxima autorizata
        mat[destinatie].push_back(make_pair(sursa,capacitate));
        mat[sursa].push_back(make_pair(destinatie, capacitate));

        if(capacitate > maxim)
            maxim=capacitate;
    }

    //facem cautare binara
    int l, r, centru;
    l=1;
    r=maxim;

    while(l<=r) {
        centru= (l+r) /2;

        if(bfs(centru)!=0)
            l=centru+1;
        else
            r=centru-1;
    }

    g<<r<<endl;
    return 0;
}