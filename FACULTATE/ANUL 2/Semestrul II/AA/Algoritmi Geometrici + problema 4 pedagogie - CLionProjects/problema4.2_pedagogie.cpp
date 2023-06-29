#include <iostream>
#include <string>
using namespace std;

bool estePalindrom(int n) {
    // Transformam numarul in sir de caractere
    string nSir = to_string(n);

    // Verificam daca șirul de caractere este palindrom
    // comparand termeni din prima jumatate cu cei din a doua
    int stanga = 0;
    int dreapta = nSir.length() - 1;
    while (left < right) {
        if (nSir[stanga] != nSir[dreapta])
            return false;
        stanga++;
        dreapta--;
    }
    return true;
}

int main()
{
    int n, numarPozitiiIdentice=0;
    cout << "n= ";
    cin >> n;

    if (estePalindrom(n))
        cout << "Numarul " << n << " este palindrom.\n";
    else{
        cout << "Numarul " << n << " este oglinditul numarului ";
        string nSir = to_string(n);
        string oglindit(nSir.rbegin(), nSir.rend());
        cout<<oglindit<<" .\n";
    }

    string nSir = to_string(n);
    string oglindit(nSir.rbegin(), nSir.rend());
    for (int i = 0; i < nSir.length(); i++)
        if (nSir[i] == oglindit[i])
            numarPozitiiIdentice++;

    cout<<"Numarul citit si oglinditul sau au aceeasi cifra pe "<<numarPozitiiIdentice<<" pozitii.";


    return 0;
}