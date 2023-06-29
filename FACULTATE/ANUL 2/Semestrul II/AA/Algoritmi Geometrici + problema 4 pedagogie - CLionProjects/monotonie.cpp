#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Punct {
    long long int x, y;
};

int main(){

    long long int n, xm=1000000001, ym=1000000001, xi, yi, x, y,ok;
    vector<long long int> pctx;
    vector<long long int> pcty;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        cin>>x;
        pctx.push_back(x);
        cin>>y;
        pcty.push_back(y);
        if(pctx[i]<xm)
            xm=pctx[i], xi=i;
        if(pcty[i]<ym)
            ym=pcty[i], yi=i;
    }

    rotate(pctx.begin(), pctx.begin()+xi, pctx.end());
    rotate(pcty.begin(), pcty.begin()+yi, pcty.end());

    ok=0;
    for(int i=0;i<pctx.size()-2;i++)
        if ( (pctx[i]>pctx[i+1] && pctx[i+1]<pctx[i+2]  ) ||
                pctx[i]<pctx[i+1] && pctx[i+1]>pctx[i+2] )
            ok++;

        if(ok>1) cout<<"NO\n";
        else cout<<"YES\n";

    ok=0;
    for(int i=0;i<pcty.size()-2;i++)
        if ( (pcty[i]>pcty[i+1] && pcty[i+1]<pcty[i+2]  ) ||
             pcty[i]<pcty[i+1] && pcty[i+1]>pcty[i+2] )
                ok++;
    if(ok>1) cout<<"NO\n";
    else cout<<"YES\n";

    return 0;
}