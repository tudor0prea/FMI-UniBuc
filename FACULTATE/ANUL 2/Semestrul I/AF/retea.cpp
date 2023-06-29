#include <stdio.h>
#include <math.h>

// MERGE si af. in consola
int m,n, f[3000];
double d[3000];

struct Punct{
    int x;
    int y;
} b[3000],v[3000];

double distanta(Punct A, Punct B) {
    return sqrt( ( (double ) A.x - B.x) * ( (double ) A.x - B.x)
                 + ( (double) A.y-B.y) * ((double) A.y-B.y));
}

double min(double x, double y) { if(x<y) return x; else return y;}



int main() {
    int i, j, c;
    double s = 0, distmin=1000000000;


    FILE *intrare; //FILE *iesire;
    intrare= fopen("retea.in","r"); //iesire=fopen("retea.out","w");

    fscanf(intrare, "%d %d", &n, &m);

    for(i=1; i<=n; i++)
        fscanf(intrare, "%d %d", &v[i].x, &v[i].y);

    for(i=1; i<=m; i++)
        fscanf(intrare, "%d %d", & b[i].x, & b[i].y);

    for(j=1;j<=m;j++)
    {d[j]=distanta (v[1],b[j]);
        for(i=1;i<=n ;i++)
            d[j]=min(d[j], distanta( v[i], b[j]));
    }

    for(i=1;i<= m; i++) {
        distmin=1000000000;


        for(j=1;j<= m; j++){
            if(f[j]==1) continue;
            if(d[j]<distmin) distmin=d[j], c=j; }
        s=s+distmin;
        f[c]=1;


        for(j=1;j<=m;j++) d[j]= min( d[j], distanta(b[c], b[j]));
    }

    printf("%6lf\n",s); //fprintf(iesire,"%6lf\n",s);



    fclose(intrare); //fclose(iesire);
    return 0;

}
