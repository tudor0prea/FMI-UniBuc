#include <stdio.h>

int r[3000], r1, r2, n;

void Initializare(int u) { r[u]=u;}

int Reprez(int u) { return r[u];}

void Reuneste(int u, int v) {
    r1=Reprez(u);
    r2=Reprez(v);
    for(int i=1; i<=n;i++)
        if(r[i]==r2)
            r[i]=r1;
}

int main() {

    // sorteaza(E)
    int nrs=0;

    for(int i=1;i<=n;i++)
        Initializare(i);

    for( (u,v) in E)
        if(Reprez(u) != Reprez(v))
        {
            // E(T) = E(T) reunit cu {uv};
            Reuneste(u,v);
            nrs++;
            if(nrs==n-1)
                break; //break;
        }
}