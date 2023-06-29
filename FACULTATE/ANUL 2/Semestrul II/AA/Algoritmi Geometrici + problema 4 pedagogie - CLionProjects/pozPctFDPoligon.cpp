#include <iostream>
#include <vector>
#include <algorithm>
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

int orientare(Punct p, Punct q, Punct r) {
    long long delta1 = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);

    if (delta1 == 0) return 0;
    else {if (delta1 < 0) return -1;
        else return 1; }
}

void verificare(Punct x, Punct M) {
    int ok=0;
    int nr_inters=0;
    for(long long int i=0;i<puncte.size()-1;i++) {
        //intai verificam daca x se afla cumva pe dreapta
        // formata din punctele i si i+1
      if (orientare(puncte[i],puncte[i+1],x) == 0) {
            cout << "BOUNDARY\n";
            ok=1;
            break;
        }
        else {

            //daca nu era pe dreapta, verificam intre dreapta xM
            //si fiecare dreapta din poligon (i,i+1)


            Punct a = puncte[i];
            Punct b = puncte[i + 1];

            Punct c = x;
            Punct d = M;

            if ( ( (orientare(a,b,c) >=0 && orientare(a,b,d) <=0) ||
                    (orientare(a,b,c) <=0 && orientare(a,b,d) >=0) )
                    &&
                    ( (orientare(c,d,a) >=0 && orientare(c,d,b) <=0) ||
                      (orientare(c,d,a) <=0 && orientare(c,d,b) >=0) )    )
                    nr_inters++;
//
//            long double coord_x = ((b.x - a.x) * (d.x * c.y - d.y * c.x) - (d.x - c.x) * (b.x * a.y - a.x * b.y)) /
//                                ((b.y - a.y) * (d.x - c.x) - (d.y - c.y) * (b.x - a.x));
//            long double coord_y = ((b.x * a.y - a.x * b.y) * (d.y - c.y) - (d.x * c.y - c.x * d.y) * (b.y - a.y)) /
//                                ((b.y - a.y) * (d.x - c.x) - (d.y - c.y) * (b.x - a.x));
//
//            if (((coord_x >= a.x && coord_x <= b.x) || (coord_x <= a.x && coord_x >= b.x)) &&
//                ((coord_y >= a.y && coord_y <= b.y) || (coord_y <= a.y && coord_y >= b.y)))
//                nr_inters++;

//             if( coord_x>=min(a.x,b.x) && coord_x<=max(a.x,b.x) && coord_y>=min(a.y,b.y)
//              && coord_y<=max(a.y,b.y))
//                 nr_inters++;
        }
    }

    //cout<<nr_inters<<endl;
    if(ok!=1) {
        if (nr_inters % 2 == 1)
            cout << "INSIDE\n";
        else
            cout << "OUTSIDE\n";
        }


}

int main() {

    long long n, m, x, y, maxx=0, maxy=0;

    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x>>y;
        if(x>maxx)
            maxx=y;
        if(y>maxy)
            maxy=y;
        puncte.push_back(Punct(x,y));

    }

    puncte.push_back(puncte[0]);

    //alegem punctul cel mai indepartat:
    Punct M;
    M.x=maxx+10000000;
    M.y=maxy+10000000;

    cin>>m;
    for(int i=0;i<m;i++)
    {
        cin>>x>>y;
        verificare(Punct(x,y), M);
    }

    return 0;
}