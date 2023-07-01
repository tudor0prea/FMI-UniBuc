#include <iostream>
#include <string.h>
#include <vector>
using namespace std;


class Contract {
   
    int nr;
    int an;
    char beneficiar[40], furnizor[50];
    float valoare;
    
public:
//      Constructori
    Contract(int numar, int anSemnare, char client[40], char furniz[50], float val)
    { nr=numar;
    an=anSemnare;
    strcpy(beneficiar, client);
    strcpy(furnizor, furniz);
    valoare=val; }
    
    Contract(const Contract &c)
    { nr=c.nr;
    an=c.an;
    strcpy(beneficiar, c.beneficiar);
    strcpy(furnizor, c.furnizor);
    valoare=c.valoare;}
    
    Contract() { nr=0; an=0; valoare=0.0;  
    strcpy(beneficiar, "nedefinit");
    strcpy(furnizor, "nedefinit"); }
    
//      Destructor
    virtual ~Contract() {};
    
//      Getteri
    char* GetBeneficiar() {return beneficiar;}
    char* GetFurnizor() {return furnizor;}
    int GetNr() {return nr;}
    int GetAn() {return an;}
    float GetValoare() {return valoare;}

//      Setteri
    void SetAn(int ann) {an=ann;}
    void SetNr(int nrn) {nr=nrn;}
    void SetValoare(float val) {valoare=val; }
    void SetBeneficiar(char* ben) { strcpy(beneficiar,ben);}
    void SetFurnizor(char* fur) { strcpy(furnizor, fur); }
//      Operatori
    Contract operator=(const Contract &c)
    {
    nr=c.nr;
    an=c.an;
    strcpy(beneficiar, c.beneficiar);
    strcpy(furnizor, c.furnizor);
    valoare=c.valoare;
    }
    
    friend ostream &operator<< (ostream &out, Contract);
    friend istream &operator>> (istream &in, Contract&);
    friend class ContractInchiriere;
    friend class Dosar;

    virtual void AplicaReducere() 
    {
        cout<<"Aveti 5% reducere la acest contract. Noul pret este: "<<valoare-0.05*valoare<<" de lei.";
    }
    
    
};


istream &operator>> (istream &in, Contract &c)
{  
    int x; char y[40]; float z;
    cout<<"Numărul contractului de închiriere: ";
    in>>x; c.SetNr(x);
    cout<<"Anul semnării contractului de închiriere: ";
    in>>x; c.SetAn(x);
    cout<<"Părțile contractante: \n    clientul: ";
    in>>y; c.SetBeneficiar(y);
    cout<<"    furnizorul: ";
    in>>y; c.SetFurnizor(y);
    cout<<"Suma pentru care s-a încheiat acest contract (lei): ";
    in>>z; c.SetValoare(z);

    return in;
}

ostream &operator<< (ostream &out, Contract c)
{  out<<"Contract nr. "<<c.GetNr()<<"/"<<c.GetAn()<<" semnat între clientul "<<c.GetBeneficiar()<<" și furnizorul "<< c.GetFurnizor()<<" pentru suma de "<<c.GetValoare()<<" (de) lei."; 
return out;
}




class ContractInchiriere: public Contract{
       //adaugam o reducere de 5% la contract (STATIC)
        static int reducere;
        int perioada;
        
    public:
    
    
    static int GetReducere() {return reducere;}   //getter pentru acea reducere(STATIC)
    int GetPerioada() {return perioada;}
    void SetPerioada(int x) {perioada=x;}
//      Constructori
    ContractInchiriere(Contract C, int per)
    { 
        nr=C.nr;
        an=C.an;
        strcpy(beneficiar,C.beneficiar);
        strcpy(furnizor,C.furnizor);
        valoare=C.valoare;
        perioada=per;
    }
    
    ContractInchiriere(const ContractInchiriere &C)
    {
        nr=C.nr;
        an=C.an;
        strcpy(beneficiar,C.beneficiar);
        strcpy(furnizor,C.furnizor);
        valoare=C.valoare;
        perioada=C.perioada;
        
    }
    
    ContractInchiriere() { nr=0; an=0; valoare=0.0;  
    strcpy(beneficiar, "nedefinit");
    strcpy(furnizor, "nedefinit"); 
    perioada=0;}
    
//      Destructor
    virtual ~ContractInchiriere() {};
    
//      Operatori
    ContractInchiriere operator=(const ContractInchiriere &c)
    {
    nr=c.nr;
    an=c.an;
    strcpy(beneficiar, c.beneficiar);
    strcpy(furnizor, c.furnizor);
    valoare=c.valoare;
    perioada=c.perioada;
    }
    friend ostream &operator<< (ostream &out, ContractInchiriere);
    friend istream &operator>> (istream &in, ContractInchiriere&);
    friend class Contract;
    friend class Dosar;

    void AplicaReducere()
    {
        cout<<endl;
        cout<<"Aveti 5% reducere la acest contract. Noul pret este: "<<this->GetValoare()-0.05*this->GetValoare()<<" de lei.";
        cout<<endl;
    }
};

int ContractInchiriere::reducere=5;
istream &operator>> (istream &in, ContractInchiriere &c)

{    int x; char y[40]; float z;


// UPCASTING!
    in>>dynamic_cast<Contract&>(c);
    
    cout<<"Perioada pentru care s-a încheiat acest contract (luni de zile): ";
    in>>x; c.SetPerioada(x);
    return in; 
}

ostream &operator<< (ostream &out, ContractInchiriere c)
{  out<<"Contractul de închiriere nr. "<<c.GetNr()<<"/"<<c.GetAn()<<" a fost semnat între clientul "<<c.GetBeneficiar()<<" și furnizorul "<< c.GetFurnizor()<<" pentru suma de "<<c.GetValoare()<<" (de) lei și perioada de "<<c.GetPerioada()<<" (de) luni de zile."; 
//out<< "Acest contract are o reducere de "<<c.GetReducere()<<"%"<<".";
return out;
}



class Dosar 
{
    int numar;
    ContractInchiriere *vector;
    
public:
    int GetNumar() {return numar;}
    
//      Constructori
    Dosar(){numar=0; vector=new ContractInchiriere [numar];}

//      Destructor
    virtual ~Dosar() { delete []vector; numar=0;}
    
//      Setter pentru numarul de contracte din dosar: 
    void SetNumar(int x) { numar=x;}
//      Metode pentru adaugare sau eliminare a contractelor din dosar
    void Adaugare(ContractInchiriere C)
    { vector[++numar]=C; }
    
    void Eliminare(int nrref, int anref)
    { 
        if(numar==0) cout<<"Nu există contracte în dosar.\n";
      else
      {
          for(int i=1; i<=numar; i++)
            if(vector[i].GetNr()==nrref && vector[i].GetAn()==anref)
                { for(int j=i+1;j<=numar;j++)
                            vector[j-1]=vector[j];
                
                    numar--;
                    i--;
                }
      }
    }  
//      Operatori
    friend ostream &operator<< (ostream &out, Dosar);
    friend istream &operator>> (istream &in, Dosar&);
    friend class ContractInchiriere;
    friend class Contract;
    
    void AfisareDosar()
    { if(numar==0)
        cout<<"Dosarul este gol.\n";
      else
      { cout<<"Dosarul conține: \n";
        for(int i=1; i<=numar;i++)
            cout<<"- contract "<<vector[i].GetNr()<<"/"<<vector[i].GetAn()<<endl;
      }
    }
    
    void ValoareTotalaContracte()
    { float s=0;
        if(numar==0)
        cout<<"Dosarul este gol. Valoarea este zero.\n";
      else
        for(int i=1; i<=numar;i++)
            s+=(vector[i].GetPerioada())*(vector[i].GetValoare());
      cout<<"Valoarea totală a contractelor din dosar este de "<<s<<" (de) lei.";
    }
    
    void ValoareContracte()
    { 
        if(numar==0)
        cout<<"Dosarul este gol. Valoarea este zero.\n";
      else
      { cout<<"Contractele din dosar:"<<endl;
        for(int i=1; i<=numar;i++)
            cout<<"- contractul "<<vector[i].GetNr()<<"/"<<vector[i].GetAn()<<" are o valoare de "<<(vector[i].GetPerioada())*(vector[i].GetValoare())<<" (de) lei."<<endl;
      }    
    }
    
    void AfisareContract(int nrref, int anref)
    { int ok=0;
        if(numar==0) cout<<"Nu există contracte în dosar.\n";
      else
      { int ok=0;
          for(int i=1; i<=numar; i++)
            if(vector[i].GetNr()==nrref && vector[i].GetAn()==anref)
                cout<<vector[i], ok=1;
            
        if(ok==0) cout<<"Acest contract nu se află în dosar.";
      }
    }
    
    void Scadere(int x, int y)
    { int ok=0;
    
     if(numar==0) cout<<"Nu există contracte în dosar.\n";
        else
        { int ok=0;
            for(int i=1; i<=numar; i++)
             if(vector[i].GetNr()==x && vector[i].GetAn()==y)
                {   cout<<vector[i]; 
                    ok=1;
                    
                    ContractInchiriere aux=vector[i];
                    cout<<endl;
                    aux.AplicaReducere(); 
                }
           if(ok==0) cout<<"Acest contract nu se afla in dosar.";
        }
    }
    
};




int main()
{ ContractInchiriere c;
    Dosar D;
    char da_sau_nu[30];
    int x, y, clientul_a_raspuns=0, tasta;
    

    cout<<"Salut! Bine ai venit în programul de organizare a contractelor tale. Mă numesc Tudor și voi fi asistentul tău."<<endl;
    cout<<"Să începem!"<<endl;
    cout<<"Răspunsul dvs:";
    cin>>da_sau_nu;
    cout<<endl;
    do{
    if(strcmp(da_sau_nu,"nu")==0 || strcmp(da_sau_nu, "NU")==0 || strcmp(da_sau_nu,"Nu")==0)
        {cout<<"Ok, îmi pare rău, ne vedem data viitoare!";
        return 0; }
        
    else if(strcmp(da_sau_nu,"da")==0 || strcmp(da_sau_nu, "Da")==0 || strcmp(da_sau_nu,"DA")==0)
        {
            cout<<"Super!Câte contracte doriți să stocați în dosar?"<<endl<<"Răspunsul dvs:";
            cin>>x;
            cout<<endl;
            cout<<"Perfect, acum mai trebuie doar să introduceți datele contractelor."<<endl;

            clientul_a_raspuns=1;
        }
        else {cout<<"Nu înțeleg ce ați spus, mai încercați.\n Răspunsul dvs:";
              cin>>da_sau_nu;}
        
    } while(clientul_a_raspuns==0);
            
        
        for(int i=1;i<=x;i++)
       { cout<<endl;
         cout<<"Contract "<<i<<endl;
           cin>>c;
         D.Adaugare(c);
         cout<<endl;}
    
    
    
    
    
    int iesire=1;
    do
    {   c.AplicaReducere(); 
           cout<<endl;
        cout<<"Iată opțiunile disponibile:\n";
        cout<<"1) Pentru a afișa conținutul dosarului dumneavoastră, apăsați tasta 1 + Enter."<<endl;
        cout<<"2) Pentru a adăuga un contract nou, apăsați tasta 2 + Enter."<<endl;
        cout<<"3) Pentru a calcula valoarea fiecărui contract de închiriere din dosar, apăsați tasta 3 + Enter."<<endl;
        cout<<"4) Pentru a calcula valoarea totală a contractelor din dosar, apăsați tasta 4 + Enter."<<endl;
        cout<<"5) Pentru a elimina un contract din dosar, apăsați tasta 5 + Enter."<<endl;
        cout<<"6) Pentru a afișa date despre un contract din dosar, apăsați tasta 6 + Enter."<<endl;
        cout<<"7) Pentru a primi reducere pentru un contract din dosar, apăsați tasta 7 + Enter."<<endl;
        cout<<"8) Pentru ieșire, apăsați tasta 0 + Enter.";
        cout<<endl;
    cout<<"\nTasta:";
    cin>>tasta;
    switch(tasta)
    {case 1: //afisare dosar
            { D.AfisareDosar();
              cout<<endl;
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
              cin>>iesire;
              break;
            }
    case 2: //adaugare contract nou
            { cin>>c;
              D.Adaugare(c);
                  cout<<endl;
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
              cin>>iesire;
              break;
            }
    case 3: //valoare contract
            { D.ValoareContracte();
                cout<<endl;
            cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
            cin>>iesire;
            break;
            }
    case 4: //valoare totala contracte
            { D.ValoareTotalaContracte();
                cout<<endl;
            cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
            cin>>iesire;
            break;
            }
    case 5: //eliminare 
            { cout<<"Numărul contractului pe care doriți să îl eliminați: ";
              cin>>x;
              cout<<"Anul semnării: ";
              cin>>y;
              D.Eliminare(x,y);
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
            cin>>iesire;
            break;
            }
             
    case 6: //afisam contract 
            { cout<<"Numărul contractului pe care doriți să îl vizualizați: ";
              cin>>x;
              cout<<"Anul semnării: ";
              cin>>y;
              D.AfisareContract(x,y);
              cout<<"\nMai doriți să efectuați vreo comandă? (da=1, nu=0)\nRăspunsul dvs: "; 
              cin>>iesire;
            break;
            }
    case 7: //reducere de pret
            { cout<<"Numărul contractului pe care doriți să îl reduceți: ";
              cin>>x;
              cout<<"Anul semnării: ";
              cin>>y;
              
              D.Scadere(x,y);
             
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