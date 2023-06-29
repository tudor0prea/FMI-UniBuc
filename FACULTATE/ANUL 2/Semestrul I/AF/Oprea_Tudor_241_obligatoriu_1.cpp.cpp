#include <iostream>
#include <vector>
using namespace std;
int i;

bool parcurgereDFS( vector<int> ordine[],vector<int> &marcat,int n){

    bool x=true;                            //incercam sa parcurgem prin DFS
    for(auto i: ordine[n])
        if(marcat[i]==-1)
        {
            marcat[i]= 1- marcat[n]; // daca un nod nu este marcat, parcurgem mai departe prin el
            x= (x && parcurgereDFS(ordine,marcat ,i) ); // facem && intre valoarea curenta a bool ului si valoarea rezultata
                                                                // din parcurgerea mai departe prin acel punct
        }
        else
            if(marcat[i]==marcat[n])    //daca este marcat si el si nodul curent, inseamna ca nu se poate
                return false;

    return x;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    vector<int> ordine[n+1];

    for(i=0; i < dislikes.size() ; i++)
    { ordine[dislikes[i][0]].push_back(dislikes[i][1]);     //daca o persoana nu o place pe una, nici cealalta nu o va place pe prima
        ordine[dislikes[i][1]].push_back(dislikes[i][0]); }

    vector<int> marcat(n+1,-1);

    bool y=true;
    for( i=1;i<=n;i++)
        if(marcat[i]==-1)
        {
            marcat[i]=1;
            y= (y && parcurgereDFS(ordine,marcat,i));
        }

    return y;
}


int main()
{ int n=5;
    vector<vector<int>> dislikes= { {1,2} , { 1,3} , {2,3}, {3,4}, {4,5}, {1,5}};


    cout<<possibleBipartition(n,dislikes);
    return 0;
}