#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

ifstream in("seminar3.in");
ifstream in2("interogari.in");
const int NMAX = 1000;
int n, k;
int Heights[NMAX], Fathers[NMAX];

void Init(int x)
{
    Fathers[x]=0;
    Heights[x]=0;

}
// find fara compresie de cale
int Find(int x) {
    while(Fathers[x])
    {x=Fathers[x];}
    return x;
}
// find cu compresie de cale, recursiv
int FindComp(int x) {
    if(Fathers[x] == 0 )
        return x;
    Fathers[x]=Find(Fathers[x]); //fathers[x] devine radacina arborelui, returnata de ap. recursiv
    return Fathers[x];
}
int Union(int x, int y) {
    int RootX = Find(x);
    int RootY = Find(y);

    //facem reuniune ponderata (dupa inaltime) - by rank
    if( Heights [ RootX ] < Heights [ RootY ])
        Fathers[RootX] = RootY; //le legam
    else if(Heights[RootX] > Heights[RootY])
            Fathers[RootY] = RootX;
        else Fathers[RootY]= RootX, Heights[RootX]++;
}

//// reuniune ponderata dupa dimensiune (nr de vf) - by size
//int UnionbySize(int x, int y) {
//    int RootX = Find(x);
//    int RootY = Find(y);
//
//    if( Heights [ RootX ] < Heights [ RootY ])
//        Fathers[RootX] = RootY; //le legam
//    else if(Heights[RootX] > Heights[RootY])
//        Fathers[RootY] = RootX;
//    else Fathers[RootY]= RootX, Heights[RootX]++;
//
//}
int main () {
    int length, x, y;
    in >> n >> k;
    for(int i=1;i<=n;i++)
        Init(i);
    for(int i=1;i<=n;i++)
    {
        in>>length;
        in>>x;
        for(int j=2;j<=length;j++)
            in>>y, Union(x,y);

    }
    cout<<n;
    for(int i = 1; i<=n; i++)
        cout<<Fathers[i]<<" ";
    cout<<endl;
    for(int i = 1; i<=n; i++)
        cout<<Heights[i]<<" ";
    cout<<endl;

//    while ( in2 >> x>> y)
//    {
//        if(Find(x) != Find (y))
//            Union(x,y), k--;
//         printf("Dupa muchia %d %d, avem %d comp conexe.\n",x,y,n);
//
//        for(int i = 1; i<=n; i++)
//            cout<<Fathers[i]<<"\n";
//        for(int i = 1; i<=n; i++)
//            cout<<Heights[i]<<"\n";
//    }
    return 0;

}

