#include <iostream>
#include <vector>
using namespace std;

// MERGE

// O(n^2)

// verif litera cu litera
// si cand doua se aseamana adaugam cate o litera

int main(){
    int i, j;
    string a,b;

    cin>>a>>b;

    int da=a.size();
    int db=b.size();

    vector<vector<int>> v(da+1, vector<int>(db+1,0));

    for(i=0;i<=da;i++)
        v[i][0]=0;

    for(j=0;j<=db;j++)
        v[0][j]=0;

    for(i=1;i<=da;i++)
        for(j=1;j<=db;j++)
            if(a[i-1]==b[j-1])
                v[i][j] = v[i-1][j-1]+1;
            else
                v[i][j]= max(v[i-1][j],v[i][j-1]);


    cout<<v[da][db];
    return 0;

}