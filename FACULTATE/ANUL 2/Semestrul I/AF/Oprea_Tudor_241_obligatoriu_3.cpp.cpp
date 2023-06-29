#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

vector<int> ordonare(int N, vector<vector<int>> &P) {
    vector<vector<int>> cursuri(N);               // lista cursurilor
    vector<int> program , precedente(N);               // numarul cursurilor care le preced pe fiecare in parte
    for (auto &pre: P)
        cursuri[pre[1]].push_back(pre[0]),            // lista ceruta
                precedente[pre[0]]++;

    queue<int> coada;

    for (int i = 0; i < N; i++)
        if (precedente[i] == 0) // cautam cursurile care nu au nevoie de niciun alt curs inaintea lor
            coada.push(i);   // si le adaugam in coada

    while (sizeof(coada) != 0) {
        int var = coada.front();
        coada.pop();    // le scoatem din coada si le adaugam in program
        program.push_back( var );

        for (int urmator: cursuri[var])
            if ( precedente[urmator] -1  == 0)
                coada.push(urmator);         // cursul care mai are 0 precedente ramase poate fi acum adaugat
                                                // il punem mai intai in coada, ca la urmatorul pas sa fie pus in program
    }
    if (sizeof(program) == N) return program;              // daca am adaugat in program toate cele n cursuri,
    return {};                                             // atunci programarea este posibila; altfel, nu
}
int main() {
int x,N;
vector<vector<int>> P;

cin>>N;
for(int i=1;i<=N;i++)
    for(int j=1;j<=2;j++)
    {cin>>x;
        P[i].push_back(x);}

vector<int> rasp= ordonare(N,P);
for(int i=1;i<=2;i++)
    cout<<rasp[i]<<" ";

return 0;

}