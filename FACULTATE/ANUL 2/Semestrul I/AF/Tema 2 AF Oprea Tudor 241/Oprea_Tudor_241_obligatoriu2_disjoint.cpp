#include <stdio.h>
#include <iostream>
#define MAXI 100001
int h[MAXI], tati[MAXI], n, m, i;

int Cauta(int a) {
    while(tati[a]!=a)
        a=tati[a];
    return a;
}

void Reuneste(int a, int b){
    if( h[a] > h[b] )
        tati[b]=a;
    else tati[a]=b;

    if(h[a]==h[b])
        h[b]++;
}

int main() {
    int a,b,c;
    freopen("disjoint.in","r",stdin);
    freopen("disjoint.out","w",stdout);

    scanf("%d %d", &n, &m);

    for(i=1;i<=n;i++) tati[i]=i,h[i]=1;

    for( ;m!=0; m--){
        scanf("%d %d %d", &c, &a, &b);

        if(c==2) {
            if (Cauta(a) == Cauta(b))
                    printf("DA");
                else
                    printf("NU"); }
        else Reuneste(Cauta(a),Cauta(b));

    }
    std::cout<<"Executat";
    return 0;
}