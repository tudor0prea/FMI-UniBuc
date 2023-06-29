#include <iostream>
#include <stack>
using namespace std;

struct Punct {
    long long int x, y;

    Punct(long long int a, long long int b) { x=a, y=b;}
    Punct() {}

    void citire () {
        cin>>x>>y;
    }

};

Punct p;

Punct urmator(stack<Punct> &stiva) {
    Punct a,b;

    a = stiva.top();
    stiva.pop();
    b = stiva.top();

    stiva.push(a);
    return b;

}

void inversare(Punct &a, Punct &b) {
    Punct aux;
    aux=a; a=b; b=aux;
}

long long int distanta(Punct a, Punct b){
    return (a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y);
}

bool viraj(Punct p, Punct q, Punct r) {
    long long int delta;
    delta = (q.x-p.x)*(r.y-p.y) - (q.y - p.y) * (r.x-p.x);

    if(delta>0) return 1; //viraj la stanga
    else return 0; //avansare
}

void infasuratoare(Punct pct[], long long int n){
    //cautam cel mai jos punct din infasuratoare

    long long int ymin = pct[1].y;
    long long int minim=0;

    for(long long int i=1;i<=n;i++){
        long long int indice=pct[i].y;

        if ((indice<ymin) || (ymin==indice && pct[i].x < pct[minim].x)) {
            ymin = pct[i].y;
            minim=i;
        }
    }

    //punctul cu indicele "minim" este cel mai de jos punct,
    //deci apare cu siguranta in infasuratoare

    //il punem primul in vector ca sa pornim din el
    //inversare(pct[1],pct[minim]);

    Punct vector[1000001];
    long long int x=1;
    for(long long int i=minim;i<=n;i++)
        vector[x++]=pct[i];
    for(long long int i=1;i<=minim-1;i++)
        vector[x++]=pct[i];

    stack<Punct> stiva;

    for(long long int i=1;i<=n;i++)
    {
        //cat timp nu avem viraje la dreapta sau avansari, scoarem punctele
        while( stiva.size()>1 && viraj(urmator(stiva), stiva.top(), vector[i]) !=1){
           stiva.pop();
        }
        stiva.push(vector[i]);

    }

    while( stiva.size()>1 && viraj(urmator(stiva), stiva.top(), vector[1]) !=1){
        stiva.pop();
    }

    cout<<stiva.size()<<endl;

    x=1;
    while(!stiva.empty()) {

        vector[x++]=stiva.top();
        //cout<<a.x<<" "<<a.y<<endl;
        stiva.pop();
    }
    for(long long int i=x-1;i>=1;i--)
        cout<<vector[i].x<<" "<<vector[i].y<<endl;
}


int main(){
    long long int n;
    Punct pct[1000001];
    cin>>n;
    for(long long int i=1;i<=n;i++)
        pct[i].citire();

    infasuratoare(pct,n);

    return 0;
}