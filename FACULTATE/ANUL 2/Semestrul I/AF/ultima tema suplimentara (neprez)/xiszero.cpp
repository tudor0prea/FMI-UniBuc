#include <iostream>
#include <fstream>
using namespace std;

/* Tabla de x si 0:
 0 1 2
 3 4 5
 6 7 8
 */

int raspuns[9999],p[9];

bool castig(int x[]) {
    //tratam toate cazurile in care un jucator castiga

    //daca avem diagonalele
    if(x[0]!=0 && x[0]==x[4] && x[4]==x[8] )
        return 1;
    if(x[2]!=0 && x[2]==x[4] && x[4]==x[6] )
        return 1;

    //daca avem o linie orizontala
    if(x[0]!=0 && x[0]==x[1] && x[1]==x[2] )
        return 1;
    if(x[3]!=0 && x[3]==x[4] && x[4]==x[5] )
        return 1;
    if(x[6]!=0 && x[6]==x[7] && x[7]==x[8] )
        return 1;

    //daca avem o linie verticala
    if(x[0]!=0 && x[0]==x[3] && x[3]==x[6] )
        return 1;
    if(x[1]!=0 && x[1]==x[4] && x[4]==x[7] )
        return 1;
    if(x[2]!=0 && x[2]==x[5] && x[5]==x[8] )
        return 1;

    //daca nu este niciun caz, atunci
    return 0;
}


int verificare(int stare) {

    if(raspuns[stare]!=0)
        return  raspuns[stare];

    int c=stare;
    int countX=0, count0=0, rezultat, ok,starenoua;
    int tabela[9];

    for(int i=0;i<=8;i++)
    {
        tabela[i]= c%3; c=c/3;

        if(tabela[i]==1) countX+=1;
        if(tabela[i]==2) count0+=1;
    }

    if(castig(tabela))
    {
        //daca a castigat cineva, verificam cine
        //castigatorul este cel care are mai multe
        // simboluri pe tabela
        if(countX > count0)
        {raspuns[stare]=1; return 1;}

        raspuns[stare]=-1;
        return -1;

    }

    if(count0+countX==9)
    {
        //daca este plina tabla
        //atunci este remiza
        raspuns[stare]=2;
        return 2;
    }

    if(count0==countX) {
        //daca sunt tot atatea simboluri x cat si 0
        //atunci inseamna ca x trebuie sa puna (el a inceput)

        raspuns[stare] = -1; //neterminat
        ok = 0;
        for (int i = 0; i <= 8; i++)
            if (tabela[i] == 0) {
                //nu poate pune aici
                starenoua = stare + p[i];
                rezultat = verificare(starenoua);

                if (rezultat == 1)
                    raspuns[stare] = 1, ok = 1;
                if (!ok && rezultat == 2)
                    raspuns[stare] = 2;
            }
    }
    else
    {
                ok = 0;
                raspuns[stare] = 1;
                for (int i = 0; i <= 8; i++)
                    if (tabela[i] == 0) {
                        starenoua = stare + 2 * p[i];
                        rezultat = verificare(starenoua);

                        if (rezultat < 0)
                            raspuns[stare] = -1, ok = 1;
                        if (!ok && rezultat == 2)
                            raspuns[stare] = 2;
                    }
    }

    return raspuns[stare];

}

int main() {

    ifstream f("xsizero.in");
    ofstream g("xsizero.out");

    int stare, pas=1;

    p[0]=1;
    for(int i=1;i<=8;i++)
        p[i]=p[i-1]*3;

    verificare(0);

    char input[10];

    while(f>>input) {
        f>> (input+3);
        f>> (input+6);
        //am citit tabela

        stare=0;
        for(int i=0;i<=8;i++) {


            if (input[i] == 'X')
                stare = stare + p[i];
            if (input[i]=='0')
                stare=stare + 2*p[i];
        }

        g<<"Testul "<<pas<<": ";
        if(raspuns[stare]==-1)
            g<<"lose"<<endl;
        else
        if(raspuns[stare] == 0)
            g<<"invalid"<<endl;
        else if(raspuns[stare]==1)
            g<<"win"<<endl;
        else g<<"draw"<<endl;

        pas=pas+1;
    }

    return 0;
}