#include <iostream>
using namespace std;
struct Punct {
    float x, y;

    Punct(float a, float b) { x=a, y=b;}
    Punct() {}

    void citire () {
        cin>>x>>y;
    }

};


int main() {
    int n, stanga=0, dreapta=0, avans=0;
    float delta;
    Punct p, q, r, copie;
    cin>>n;

    p.citire();
    copie=Punct(p.x,p.y);
    q.citire();

    for(int i=1;i<=n-2;i++) {


        r.citire();


        delta = (q.x-p.x)*(r.y-p.y) - (q.y - p.y) * (r.x-p.x);

        if(delta>0) stanga++;
        else if(delta<0) dreapta++;
        else avans++;


        p=Punct(q.x,q.y);
        q=Punct(r.x,r.y);
    }

    //mai avem de calculat p,q,copie
    delta = (q.x-p.x)*(copie.y-p.y) - (q.y - p.y) * (copie.x-p.x);

    if(delta>0) stanga++;
    else if(delta<0) dreapta++;
    else avans++;

    cout<<stanga<<" "<<dreapta<<" "<<avans<<endl;
    return 0;
}