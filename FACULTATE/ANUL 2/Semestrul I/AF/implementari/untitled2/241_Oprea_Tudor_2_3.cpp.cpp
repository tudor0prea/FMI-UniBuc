#include <vector>
#include <set>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

int n, m;
int g[999], t[999],s[999];

ifstream f("calculatoare.in");

int main() {
    f>>n>>m;

    for(int i=1;i<=n;i++)
    {
        f>>g[i];
    }

    for(int i=1;i<=m;i++)
        f>>t[i];

    for(int i=1;i<=n;i++)
        f>>s[i];
