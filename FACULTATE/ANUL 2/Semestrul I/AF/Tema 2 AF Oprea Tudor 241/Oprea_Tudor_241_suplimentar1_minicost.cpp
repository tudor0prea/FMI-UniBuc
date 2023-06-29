#include <iostream>
#include <numeric>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <math.h>
using namespace std;



//struct Punct { int x, y;};
//vector<int> tati;
//vector <vector<int> > puncte;


int GasesteTata(vector<int> &tati, int x) {
    if(tati[x]!=x)
        tati[x]=GasesteTata(tati, tati[x]);
    return tati[x];
}

int minCost(vector<vector<int>>& puncte){

    int nr_puncte=puncte.size();

    vector<int> tati(nr_puncte);
//    for(auto i:tati)
//        tati[i]=0;
    iota(tati.begin(), tati.end(), 0); //init vectorul cu 0

    int a=0, muchii=0;

    priority_queue < vector<int> > coada;

    // adaugam distanta dintre fiecare doua puncte in coada de prioritati
    // sub forma (distanta, punct1, punct2)
    for(int i=0;i<nr_puncte;i++)
        for(int j=i+1;j<nr_puncte;j++)
            if(i!=j)
                coada.push( { (-1) * ( abs(puncte[i][0] - puncte[j][0]) +
                                    abs(puncte[i][1]-puncte[j][1])),
                                    i,
                                    j});

    while(muchii != nr_puncte-1)
        { //pana cand gasim destule muchii intre pct
        vector<int> muchie = coada.top();

        int tata1= GasesteTata(tati,muchie[1]);
        int tata2= GasesteTata(tati, muchie[2]);

        if(tata1 != tata2) {
            a=a+ (-1)*muchie[0]; //adaugam lungimea muchiei
        tati[tata1]=tata2;

        muchii++;
        }
        coada.pop();
        }

        return a;
}

int main() {
    //testam cu exemplul dat
    vector <vector<int> > puncte = {{3,12},{-2,5},{-4,1}};
    cout<<minCost(puncte);
    cout<<"executat";
}