#include <iostream>

using namespace std;

//dorim cel mai scurt sir care sa contina toate
//subsecventele date


#include <bits/stdc++.h>
using namespace std;


// Variabile globale
int N; // Numarul de secvente de ADN
string shortestString; // Sirul cel mai scurt care contine toate secventele ca subsecvente
int shortest; // Lungimea sirului cel mai scurt
string sir[9999];

// Functia DFS care cauta sirul cel mai scurt
void DFS(int n, string result) {
    // Daca am parcurs toate secventele de ADN si am gasit
    // un sir mai scurt decat cel mai scurt gasit pana acum,
    // actualizam valorile variabilelor shortest si shortestString
    if (n == N) {
        if (result.length() < shortest) {
            shortest = result.length();
            shortestString = result;
        }
        return;
    }

    // Verificam daca secventa curenta poate fi adaugata la sfarsitul l

    //Sirului result. Daca da, adaugam secventa la sfarsitul lui result
    // si apelam DFS recursiv cu result actualizat.
    // Dupa ce apelul recursiv s-a terminat, eliminam ultima secventa adaugata
    // din result pentru a permite explorarea altor posibilitati.
    for (int i = 0; i < N; i++) {
        string ADN = sir[n];// secventa curenta de ADN
        if (result.find(ADN) == string::npos) {
            result += ADN;
            DFS(n + 1, result);
            result.erase(result.length() - ADN.length(), ADN.length());
        }
    }
}

int main() {
// Citim numarul de secvente de ADN si cele N secvente
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> sir[i];
    }

    // Initializam variabilele globale
    shortest = INT_MAX;
    string result = ""; // Sirul care retine rezultatul nostru final

// Apelam functia DFS
    DFS(0, result);

// Scriem rezultatul in fisierul de iesire
    ofstream out("adn.out");
    out << shortestString << endl;
    out.close();

    return 0;
}
