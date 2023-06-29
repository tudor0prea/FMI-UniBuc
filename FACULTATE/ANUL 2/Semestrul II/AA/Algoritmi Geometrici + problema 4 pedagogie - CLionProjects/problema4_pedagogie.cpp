#include <iostream>
using namespace std;

int main(){
    int n, copie, oglindit=0, numarPozitiiIdentice=0, cifra;

    cout<<"n=";
    cin>>n;

    //Ii facem o copie lui n
    copie=n;

    while(copie!=0){

        cifra = copie%10;
        oglindit=oglindit*10 + cifra;
        copie=copie/10;

    }

    //Daca numarul n (initial) are aceeasi valoare cu oglinditul
    if(n==oglindit)
        cout<<"Numarul "<<n<<" este palindrom.";
    else
        cout<<"Numarul "<<oglindit<<" este oglinditul numarului "<<n<<" .";

    cout<<endl;
    //Pentru punctul b), verificam simultan
    // daca ultima cifra din n este egala cu ultima din oglindit

    while(n!=0){
        cifra=n%10;
        if(cifra==oglindit%10)
            numarPozitiiIdentice++;

        n=n/10;
        oglindit=oglindit/10;
    }
    cout<<"Numarul citit si oglinditul sau au aceeasi cifra pe "<<numarPozitiiIdentice<<" pozitii.";


    return 0;
}



//este suficient while n!=0 pentru ca oglinditul lui n va avea
//cel mult atatea cifre cate are si n