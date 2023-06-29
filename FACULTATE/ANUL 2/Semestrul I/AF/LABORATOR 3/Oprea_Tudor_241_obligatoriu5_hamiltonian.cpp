#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include<math.h>
using namespace std;
//MERGEE!
// idee: orice nod poate avea 2^n stari
//          in functie de masca

// O(n * n * 2^n)

int shortestPathLength(vector<vector<int>> &p){
    int cardinal=p.size();

    int rasp=0;

    set<pair<int,int>> multime;
    queue<vector<int>> coada;


    //facem bfs din toate nodurile
    for(int i=0;i<cardinal;i++)
    {
        int masca=pow(2,i);

        vector<int> mem(3,0);
        //in acest vector cu 3 pozitii initializate cu 0
        // punem masca, costul si nodul
        // exact in aceasta ordine
        mem[0]=0; //costul
        mem[1]=i; //nodul
        mem[2]=masca; //masca


        coada.push(mem);
        multime.insert({i,masca});


    }

    while(coada.size())
    {
        auto f=coada.front(); coada.pop();
        if(f[2]==pow(2,cardinal)-1)
        {//daca masca nodului este 2^n-1
            // inseamna ca am gasit costul
            rasp=f[0];

            break;
        }

        for(auto j : p[f[1]]){
            int masca=f[2] | int(pow(2,j)); // bitwise OR

            if(multime.find({j,masca})==multime.end()){
                multime.insert({j,masca});


                vector<int> mem(3,0);
                mem[0]=f[0]+1;
                mem[1]=j;
                mem[2]=masca;

                coada.push(mem);
            }
        }

    }
    return rasp;
}

int main(){
    vector<vector<int>> p={{1,2,3},{0},{0},{0}};
    cout<<shortestPathLength(p);

    return 0;
}