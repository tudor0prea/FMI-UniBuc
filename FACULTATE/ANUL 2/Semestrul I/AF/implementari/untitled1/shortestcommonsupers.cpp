#include <iostream>
#include <vector>
using namespace std;

// MERGE

// o(n*m)

// verif litera cu litera
// si cand doua se aseamana adaugam cate o litera

//https://leetcode.com/problems/longest-common-subsequence/solutions/2915593/c-100-fatster-0ms-simple-and-precise-dp-tabulation/
int main() {

    // codul de la LCS, dar nu cu lungimi, ci cu cuvinte :
    int i, j;
    string a, b;

    cin >> a >> b;

    int da = a.size();
    int db = b.size();

    //string in loc de int
    vector<vector<string>> v(da + 1, vector<string>(db + 1, ""));

//    for (i = 0; i <= da; i++)
//        v[i][0] = 0;
//
//    for (j = 0; j <= db; j++)
//        v[0][j] = 0;

    for (i = 1; i <= da; i++)
        for (j = 1; j <= db; j++)
            if (a[i - 1] == b[j - 1])
                v[i][j] = v[i - 1][j - 1] + a[i-1]; //+a[i-1] in loc de +1
            else    // inainte luam lungimea max, acum luam
                    //stringul de lungime max
                if(v[i-1][j].size() > v[i][j-1].size())
                v[i][j] = v[i - 1][j];
                else v[i][j]=v[i][j - 1];

    // memoram LCS intr o variabila
    string lcs=v[da][db];


    i=0; j=0;
    string rasp="";

    for(auto litera: lcs){

        while(a[i]!= litera)
            rasp=rasp+a[i], i++;

        while(b[j]!= litera)
            rasp=rasp+b[j], j++;

        rasp=rasp+litera;
        i++;
        j++;
    }
    cout<<rasp+a.substr(i)+b.substr(j);

    return 0;

}