#include <iostream>
#include <math.h>
using namespace std;


class Complex
{
    double parte_reala, parte_imaginara;

public:

    double GetParteReala() {return parte_reala;}
    double GetParteImaginara() {return parte_imaginara;}
    double SetParteReala(double n) {parte_reala=n;}
    double SetParteImaginara(double n) {parte_imaginara=n;}

     void Afisare()
    { Complex c;
    if( parte_reala==0 && parte_imaginara==0)
    cout<<0;
    else
    {if (parte_reala!=0)
        cout<<parte_reala;
    if (parte_imaginara>0)
        {if(parte_reala!=0)
        cout<<"+"<<parte_imaginara<<"*i";
        else cout<<parte_imaginara<<"*i";}
    else if(parte_imaginara<0)
            cout<<parte_imaginara<<"*i";
    }
    }

    //1. Constructor fara parametrii
    Complex() {parte_reala=parte_imaginara=0;}

    //2. Constructor
    Complex(double d, double s) {parte_reala=d, parte_imaginara=s;}

    //3. Constructor de copiere
    Complex(Complex &c):
        parte_reala(c.parte_reala),
        parte_imaginara(c.parte_imaginara) {}

    //4. Destructor
    ~Complex() {}

    //5. Suprascrierea operatorului de adunare
    Complex operator+ (Complex c)
    {   parte_reala+=c.parte_reala;
        parte_imaginara+=c.parte_imaginara;
    }

    //6. Calculul modulului
    double Abs() {return sqrt(parte_reala*parte_reala+parte_imaginara*parte_imaginara);}


    // Zona de "prieteni"
    friend istream &operator>>(istream &in, Complex);
    friend class ComplexVector;
};



//citire numar complex
    istream &operator>> (istream& in, Complex c)
    {   in>>c.parte_reala>>c.parte_imaginara;
            return in;}




class ComplexVector
{
    int numar_elemente;
    Complex *vector;

public:

    //1. Getter pentru dimensiunea vectorului
    int GetSize() {return numar_elemente;}

    //2. Constructor - vector cu n elemente
    ComplexVector(int nr_elem)
    {
        numar_elemente=nr_elem;
        vector=new Complex[nr_elem];
    }

    //3. Constructor fara parametrii
    ComplexVector() {numar_elemente=0, vector=new Complex[0];}

    //4. Constructor pentru initializarea vectorului cu un numar
    ComplexVector(int c, int nr_elem)
    {
         numar_elemente=nr_elem;
         vector=new Complex[numar_elemente];
         for(int i=1;i<=numar_elemente;i++)
            vector[i].parte_reala=c, vector[i].parte_imaginara=c;
    }

    // 5. Constructor de copiere
    ComplexVector(ComplexVector& v)
    {
        numar_elemente=v.numar_elemente;
        vector=v.vector;
    }

    //6. Destructor
    ~ComplexVector() {delete[] vector, numar_elemente=0;}

    //7. Suma elementelor
    Complex SumaElementelor()
    {   Complex s;
        for(int i=1;i<=numar_elemente;i++)
            {s.parte_reala+=vector[i].parte_reala;
             s.parte_imaginara+=vector[i].parte_imaginara;
            }
    return s;
    }

    //8. Vector de module
    double* VectorulModulelor()
    {   double* u;

        int elemente=GetSize();
        for(int i=1;i<=elemente;i++)
            u[i]=vector[i].Abs();
    return u;
    }

    //9. Sortare crescatoare dupa module
    void SortareCrescatoare()
    { int numar_elemente=GetSize();
    for(int i=1;i<numar_elemente;i++)
        for(int j=i+1;j<=numar_elemente;j++)
            //comparam vector[i] cu vector[j]
            if (vector[i].Abs() > vector[j].Abs())
                // le interschimbam
               {swap (vector[i].parte_reala, vector[j].parte_reala);
                swap (vector[i].parte_imaginara, vector[j].parte_imaginara);
               }
    }

    friend istream &operator>>(istream &in, ComplexVector v);
};




int main()
{
     ComplexVector( v4,7);
     int s=v.GetSize();
     for(i=1;i<=n;i++)
        v.vector[i].Afisare();

     return 0;}

}


