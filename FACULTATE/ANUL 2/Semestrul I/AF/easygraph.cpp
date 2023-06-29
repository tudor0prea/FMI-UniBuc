#include <stdio.h>
#include <vector>
using namespace std;
//VARIANTA ASTA MERGE
vector<int> G[10000];
int i, viz[10000], po[10000], nr, n, m, v[10000];

void SortareTopologica(int a){
    viz[a]=1;
    vector <int>::iterator it;
    for(it = G[a].begin(); it != G[a].end(); ++it)
        if(viz[*it]==0)
            SortareTopologica(*it);
    nr++;
    po[nr]=a; //post ordine
}

int main(){
    int T, a, b;

    freopen("easygraph.in","r",stdin);
    freopen("easygraph.out","w",stdout);

    scanf("%d",&T);
    while(T>=1){
        scanf("%d %d",&n,&m);

        for(i=1;i<=n;i++)
            scanf("%d",&v[i]);

        for(i=1;i<=m;i++)
            scanf("%d %d",&a,&b), G[a].push_back(b);

        for(i=1;i<=n;i++)
            if(viz[i]==0)
                SortareTopologica(i);

        vector <int>::iterator it;
        for(i = n; i > 0; i--)
        {
            a = po[i];
            for(it = G[a].begin(); it != G[a].end(); ++it)
                if(v[*it] < v[a]+v[*it])
                    v[*it]=v[a]+v[*it];

        }

        int s=v[1];
        for(i=2;i<=n;i++)
            if(v[i]>s)
                s=v[i];

        printf("%d\n",s);

        for(i=1;i<=n;i++)
        {
            v[i]=0;
            viz[i]=0;
            G[i].clear();
        }
        nr=0;
        T--;

    }

    return 0;

}