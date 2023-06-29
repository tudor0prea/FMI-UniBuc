#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include<unordered_map>
using namespace std;

//MERGE


// alg lui Hieholzer
set<int> multime;
unordered_map<int, int> intrare, iesire;
unordered_map<int, vector<int>> a;
stack<int> stiva;


void dfs(int nod){
    while(iesire[nod]) //cat timp putem gasi muchii
        //care sa iasa din nod
    {
        iesire[nod]--;
        int x=a[nod][iesire[nod]];
        dfs(x);
    }

    stiva.push(nod);//adaugam in stiva nodurile
    //prin care am trecut

}
vector<vector<int>> validArrangement(vector<vector<int>> &p){


    vector<vector<int>> aranjament ; //ce se va returna

    //se va da ca argument multimea de perechi
    int cardinal=p.size();

    for(auto &i: p){
        int x=i[0],y=i[1];

        //avem o muchie de la x la y, deci:
        iesire[x]+=1;
        intrare[y]+=1;

        a[x].push_back(y);

        multime.insert(x); multime.insert(y);

    }
    auto j=multime.begin();
    int s = * j; //de unde vom porni

    for(auto k : multime) {
        if( intrare[k] >= iesire[k]) continue;
        s=k;
    }
    //daca toate nodurile au intrare[i]==iesire[i],
    // graful este eulerian, deci putem porni din primul nod

    //daca un nod are iesire[i]>intrare[i] putem
    //porni din el

    //pornim un dfs din nodul de start:
    dfs(s);




    int inceput=stiva.top();
    stiva.pop();

    while(stiva.size()!=0){
        int sfarsit=stiva.top();
        stiva.pop();

        aranjament.push_back({inceput,sfarsit});
        inceput=sfarsit;

    }
    return aranjament;
}

int main(){

    //vector<vector<int>> perechi = {{5,1},{4,5},{11,9},{9,4}};
    //vector<vector<int>> perechi = {{1,3},{3,2},{2,1}};
    vector<vector<int>> perechi = {{1,2},{1,3},{2,1}};

    vector<vector<int>> raspuns;

    raspuns=validArrangement(perechi);

    for(auto i: raspuns)
        cout<<"["<<i[0]<<","<<i[1]<<"] ";


    return 0;


}

