#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;


struct Punct {
    long long int x, y;
    Punct(long long int a, long long int b) { x=a, y=b;}
    Punct() {}

    void citire () {
        cin>>x>>y;
    }
};

vector<Punct> puncte;
long long n;

float aria(Punct A, Punct B, Punct C) {

    float l1=sqrt(((B.x-A.x)*(B.x-A.x))+((B.y-A.y)*(B.y-A.y)));
    float l2=sqrt(((C.x-B.x)*(C.x-B.x))+((C.y-B.y)*(C.y-B.y)));
    float l3=sqrt(((A.x-C.x)*(A.x-C.x))+((A.y-C.y)*(A.y-C.y)));

    float p=((l1+l2+l3)/2);

    return sqrt(p*(p-l1)*(p-l2)*(p-l3));
}

int orientare(Punct p, Punct q, Punct r) {
    long long delta1 = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);

    if (delta1 == 0) return 0;
    else {if (delta1 < 0) return -1;
        else return 1; }
}


void verificare(Punct k) {
    //intai vedem daca punctul nu e cumva in stanga dreptei p0pn si
    // in dreapta p0p1

    Punct p, q, r;
    p = puncte[0];
    q = puncte[n];
    r=k;
    long long delta1 = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);

    q = puncte[1];
    long long delta2 = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    // <0 dr

    // ||
    if(orientare(puncte[0],puncte[1],k) == 0)
    {cout<<"BOUNDARY\n"; return; }

    if(orientare(puncte[0],puncte[n-1],k) == 0)
    {cout<<"BOUNDARY\n"; return; }

    if (delta1 > 0 && delta2 < 0) {
        cout << "OUTSIDE\n";
    } else {
        //gasim un ultim punct pentru care x e inca in stanga dreptei
        int coord;

        Punct p = puncte[0];
        Punct r = k;

        int stg, dr, mij;

        stg = 1;
        dr = n - 1;
        while (stg < dr) {
            mij = (stg + dr) / 2;

            Punct q = puncte[mij];
            long long delta1 = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);

            if (delta1 > 0)
                stg = mij + 1;
            else
                dr = mij;

            //cout<<stg<<" "<<mij<<" "<<dr<<endl;
        }


        coord = dr - 1;
        //if (gasit) {
        //avem triungiul format din puncte[0], puncte[coord], puncte[coord+1]

        if(orientare(puncte[coord],puncte[coord+1],k) == 0)
            cout<<"BOUNDARY\n";
        else if (orientare(puncte[0],puncte[coord],k) >=0 &&
                    orientare(puncte[0],puncte[coord+1],k) <=0 &&
                    orientare(puncte[coord],puncte[coord+1],k) >= 0 )
                    cout<<"INSIDE\n";
        else cout<<"OUTSIDE\n";




//        float ariaMare = aria(puncte[0], puncte[coord], puncte[coord + 1]);
//        float aria1 = aria(k, puncte[coord], puncte[coord + 1]);
//        float aria2 = aria(puncte[0], k, puncte[coord + 1]);
//        float aria3 = aria(puncte[0], puncte[coord], k);

        //cout<<ariaMare<<" "<<aria1<<" "<<aria2<<" "<<aria3<<endl;

/*
        //verificam daca pct se afla cumva pe dreapta
        //Punct p, q, r;
        p = puncte[coord];
        q = puncte[coord + 1];
        r = k;
        if ((q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x) == 0)
            cout << "BOUNDARY\n";
        else {
            //daca nu, verificam daca se afla in triunghi
            if ( long long int(ariaMare * 100000000) ==
                long long int(aria1 * 100000000 + aria2 * 100000000 + aria3 * 100000000)  )
                cout << "INSIDE\n";
            else {
                cout << "OUTSIDE\n";
                //cout<<ariaMare<<" "<<aria1<<" "<<aria2<<" "<<aria3<<endl;}

            }
            //}
            //else cout << "negasit";
        }
*/
    }
}


int main() {

    long long m, x, y;

    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        puncte.push_back(Punct(x,y));

    }


    cin>>m;
    for(int i=0;i<m;i++)
    {
        cin>>x>>y;
        verificare(Punct(x,y));
    }

    return 0;
}