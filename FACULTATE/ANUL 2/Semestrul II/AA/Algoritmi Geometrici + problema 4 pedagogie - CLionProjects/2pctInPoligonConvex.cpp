#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Punct {
    long long x, y;

    Punct(long long a, long long b) { x=a, y=b;}
    Punct() {}

    void citire () {
        cin>>x>>y;
    }
    Punct operator+(Punct p) {return Punct(x+p.x,y+p.y);}
    Punct operator-(Punct p) {return Punct(x-p.x, y-p.y);}

    long long cross(Punct B){ return x*B.y - y*B.x;}
    long long cross(Punct B, Punct C) {return (B-*this).cross(C-*this);}
    long long dot(Punct B) { return x*B.x + y*B.y;}
    long long sqrLen() {return this->dot(*this);}
};

bool lexComp( Punct &s, Punct &d) {
    if(s.x < d.x || (s.x==d.x && s.y<d.y))
        return true;
    else
        return false;
}

int semn(long long x){
    if(x>0)
        return 1;
    else if(x==0)
        return 0;
    else return -1;
}

vector<Punct> l;
Punct A;
int n;


bool pctInTriunghi(Punct A, Punct B, Punct C, Punct V){
    long long s1= abs(A.cross(B, C));
    long long s2= abs(V.cross(A,B)) +
            abs(V.cross(B,C)) +
            abs(V.cross(C,A));
    if(s1==s2)
        return true;
    else
        return false;
}

void prep(vector<Punct> v){
    n=v.size();
    int x=0;
    for(int i=1;i<n;i++) {
        if(lexComp(v[i],v[x]))
            x=i;
    }

    rotate(v.begin(),v.begin() + x, v.end());

    n=n-1;
    l.resize(n);
    for(int i=0;i<n;i++)
        l[i]=v[i+1]-v[0];

    A=v[0];
}

bool punctInPoligon(Punct P){
    P=P-A;

    if(l[0].cross(P) !=1 &&
        semn(l[0].cross(P)) != semn(l[n-1].cross(l[0])))
        return false;
    if(l[n-1].cross(P) &&
            semn(l[n-1].cross(P)) != semn(l[n-1].cross(l[0])))
        return false;

    if(! l[0].cross(P) )
        return l[0].sqrLen() >= P.sqrLen();

    int stg=0;
    int dr=n-1;
    while(dr-stg >1) {
        int c = (stg+dr)/2;
        int centru=c;
        if(l[centru].cross(P) >=0)
            stg=centru;
        else
            dr=centru;
    }
    int pos=stg;
    return pctInTriunghi(l[pos], l[pos+1], Punct(0,0), P);
}

int main() {
    long long n, m;
    Punct A;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>l[i].x>>l[i].y;

    cin>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>A.x>>A.y;

        cout<<"citit";
        if(punctInPoligon(A))
            cout<<"INSIDE";
        else
            cout<<"OUTSIDE";
        }

    return 0;
}