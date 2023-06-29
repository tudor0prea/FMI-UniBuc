#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector <int> pozitii(100001);
vector <int> rez, permutare;
vector <int> vizitat(10001,0);

vector<vector<int>> g(10001);


void parcurgereDFS(const int &x, vector<int> vizitat)
{
    rez.push_back(x); //adaugam nodul in rezultat
    vizitat[x]=1; //marcam nodul drept vizitat
    for(auto i:g[x])
    {
        if(!vizitat[i])     //daca un nod adiacent lui x nu a fost vizitat
            parcurgereDFS(i,vizitat);   // atunci mergem mai departe prin el
    }

}

bool compar( int a, int b)
{ return pozitii[a]<pozitii[b]; }

int main()
{
    int i, m, n, a, b;
    cin>>n>>m; //numar de noduri, numar de muchii

    for(i=1;i<=n;i++)
    {
        cin>>a;         //citim nodul
        pozitii[a]=i;   // ii marcam pozitia in cadrul permutarii
        permutare.push_back(a);  //il adaugam in vectorul permutare
    }

    for(i=1;i<=m;i++)
    {
        cin>>a;
        cin>>b; //citim capetele muchiei a,b
        g[a].push_back(b); //il adaugam pe b in lista de adiacenta a lui a
        g[b].push_back(a); //si pe a in cea a lui b
    }

    for(i=1;i<=n;i++)
    {
        sort(g[i].begin(), g[i].end(), compar);
        //asezam nodurile in liste asa cum ar trebui vizitate
        // adica ne luam dupa pozitia lor din permutare

    }

    parcurgereDFS(1,vizitat); //incepem parcurgerea
    for(i=0;i<n;i++)
        if(rez[i]!=permutare[i])
        {
            cout<<0;
            return 0;
        }

    cout<<1;
    return 0;

}