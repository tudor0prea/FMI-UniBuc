#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;


class Complex
{
    double parte_reala, parte_imaginara;

public:

    double GetParteReala() {return parte_reala;}
    double GetParteImaginara() {return parte_imaginara;}
    double SetParteReala(double n) {parte_reala=n;}
    double SetParteImaginara(double n) {parte_imaginara=n;}

    ostream& operator<< (ostream &out)
    {
        //Algoritm afisare numar complex
        if( parte_reala==0 && parte_imaginara==0)
            out<<0;
        else
        {
            if (parte_reala!=0)
                out<<parte_reala;
            if (parte_imaginara>0)
            {
                if(parte_reala!=0)
                    out<<"+"<<parte_imaginara<<"*i";
                else out<<parte_imaginara<<"*i";
            }
            else if(parte_imaginara<0)
                out<<parte_imaginara<<"*i";
        }
        return out;
    }
    
    istream& operator>> (istream &in)
    { in>>parte_reala>>parte_imaginara;
    return in;}

    //1. Constructor fara parametrii
    Complex()
    {
        parte_reala=parte_imaginara=0;
    }

    //2. Constructor
    Complex(double d, double s)
    {
        parte_reala=d, parte_imaginara=s;
    }

    //3. Constructor de copiere
    Complex(Complex &c):
        parte_reala(c.parte_reala),
        parte_imaginara(c.parte_imaginara) {}

    //4. Destructor
    ~Complex() {}

    //5. Suprascrierea operatorului de adunare
    Complex operator+ (Complex c)
    {
        parte_reala+=c.parte_reala;
        parte_imaginara+=c.parte_imaginara;
    }

    //6. Calculul modulului
    double Abs()
    {
        return sqrt(parte_reala*parte_reala+parte_imaginara*parte_imaginara);
    }

    friend class ComplexVector;
};





class ComplexVector
{
    int numar_elemente;
    Complex *vector;

public:
    friend class Complex;
    //1. Getter pentru dimensiunea vectorului
    int GetSize()
    {
        return numar_elemente;
    }

    //2. Constructor - vector cu n elemente
    ComplexVector(int nr_elem)
    {
        numar_elemente=nr_elem;
        vector=new Complex[nr_elem+1];
    }

    //3. Constructor fara parametrii
    ComplexVector()
    {
        numar_elemente=0, vector= {0};
    }

    //4. Constructor pentru initializarea vectorului cu un numar
    ComplexVector(int c, int nr_elem)
    {
        numar_elemente=nr_elem;
        vector=new Complex[numar_elemente+1];
        for(int i=1; i<=numar_elemente; i++)
            vector[i].parte_reala=c, vector[i].parte_imaginara=c;
    }

    // 5. Constructor de copiere
    ComplexVector(const ComplexVector& v)
    {
        numar_elemente=v.numar_elemente;
        vector=v.vector;
    }

    //6. Destructor
    ~ComplexVector()
    {
        delete[] vector, numar_elemente=0;
    }

    //7. Suma elementelor
    Complex SumaElementelor()
    {
        Complex s;
        for(int i=1; i<=numar_elemente; i++)
        {
            s.parte_reala+=vector[i].parte_reala;
            s.parte_imaginara+=vector[i].parte_imaginara;
        }
        return s;
    }

    //8. Vector de module
    double* VectorulModulelor()
    {
        int elemente=GetSize();
        double *u=new double [elemente];
        for(int i=1; i<=elemente; i++)
            u[i]=vector[i].Abs();
            
        return u;
    }
    
    void AfisareVectorModule()
    { int elem=GetSize();
      double* u=VectorulModulelor();
      for(int i=1;i<=elem;i++)
        cout<<u[i]<<" ";
    }

    //9. Sortare crescatoare dupa module
    void SortareCrescatoare()
    {
        int numar_elemente=GetSize();
        for(int i=1; i<numar_elemente; i++)
            for(int j=i+1; j<=numar_elemente; j++)
                //comparam vector[i] cu vector[j]
                if (vector[i].Abs() > vector[j].Abs())
                    // le interschimbam
                {
                    swap (vector[i].parte_reala, vector[j].parte_reala);
                    swap (vector[i].parte_imaginara, vector[j].parte_imaginara);
                }
    }

    //10. Metoda de Afisare si citire

    ostream& operator<< (ostream &out)
    { for(int i=1; i<=numar_elemente; i++)
        {
            vector[i].operator<<(out);
            out<<" ";
        }
        
    return out;
    }
    
    istream& operator>> (istream &in)
    {
        for(int i=1; i<=numar_elemente; i++)
            vector[i].operator>>(in);

        return in;
    }

 };

int main()
{   char da_sau_nu[30];
    
    int numar_elemente, clientul_a_raspuns=0, tasta;
    
    cout<<"Salut! Acest program construiește un vector de numere complexe. Hai să începem!";
    cout<<endl;
    cout<<"Răspunsul dvs:";
    cin>>da_sau_nu;
    cout<<endl;
    do{
    if(strcmp(da_sau_nu,"nu")==0 || strcmp(da_sau_nu, "NU")==0 || strcmp(da_sau_nu,"Nu")==0)
        {cout<<"Ok, îmi pare rău, ne vedem data viitoare!";
        return 0; }
        
    else if(strcmp(da_sau_nu,"da")==0 || strcmp(da_sau_nu, "Da")==0 || strcmp(da_sau_nu,"DA")==0)
        {
            cout<<"Super!Câte elemente doriți să aibă vectorul?"<<endl<<"Răspunsul dvs:";
            cin>>numar_elemente;
            cout<<endl;
            cout<<"Perfect, acum mai trebuie doar să introduceți valorile. \nPentru fiecare număr complex, tastați întâi partea reală, apoi pe cea imaginară."<<endl<<"Răspunsul dvs:";

            clientul_a_raspuns=1;
        }
        else {cout<<"Nu înțeleg ce ați spus, mai încercați.\n Răspunsul dvs:";
              cin>>da_sau_nu;}
        
    } while(clientul_a_raspuns==0);
        
            ComplexVector v(numar_elemente);
            v.operator>>(cin);
            cout<<"Așa arată vectorul dvs în acest moment:"<<endl;
            v.operator<<(cout);
            cout<<endl;
            
    cout<<"\nAcum avem vectorul de numere complexe memorat!"<<endl;
        
    
    int iesire=1;
    do
    {       cout<<endl;
        cout<<"Iată opțiunile disponibile:\n";
        cout<<"1) Pentru a determina Vectorul Modulelor, apasă tasta 1 + Enter."<<endl;
        cout<<"2) Pentru a sorta vectorul crescător, după module, apasă tasta 2 + Enter."<<endl;
        cout<<"3) Pentru a calcula suma tuturor elementelor din vector, apasă tasta 3 + Enter."<<endl;
        cout<<"4) Pentru ieșire, apasă tasta 0 + Enter.";
        cout<<endl;
    cout<<"\nTasta:";
    cin>>tasta;
    switch(tasta)
    {case 1: //VectorulModulelor
            { cout<<"Acesta este vectorul modulelor: \n";
              v.AfisareVectorModule();
                  cout<<endl;
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
              cin>>iesire;
              break;
            }
    case 2: //SortareCrescatoare
            { cout<<"Așa arată vectorul dvs sortat crescător după module:"<<endl;
              v.SortareCrescatoare();
              v.operator<<(cout);
                  cout<<endl;
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
              cin>>iesire;
              break;
            }
    case 3: //SumaElementelor
            {cout<<"Suma elementelor din vectorul dvs este:"<<endl;
            v.SumaElementelor().operator<<(cout);
                cout<<endl;
            cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
            cin>>iesire;
            break;
            }
    case 0: //iesire din program
            { cout<<"La revedere!\n";
                return 0;}
    default: {cout<<"Această comandă nu există. Doriți să încercați din nou:\n";
              cout<<"Răspunsul dvs:";
              cin>>iesire;
              
            }
    }
    } while(iesire==1);
        
    cout<<"La revedere!";
    
    
    return 0;
}