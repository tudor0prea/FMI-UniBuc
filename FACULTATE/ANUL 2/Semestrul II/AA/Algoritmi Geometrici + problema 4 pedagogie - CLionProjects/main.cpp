#include <iostream>
using namespace std;
struct Punct {
    float x, y;

    Punct(float a, float b) { x=a, y=b;}
    Punct() {}

    void citire () {
        cin>>x>>y;
    }

};


int main() {
    int t, delta;

    cin>>t;

    for(int i=1;i<=t;i++) {
        Punct p, q, r;
        p.citire();
        q.citire();
        r.citire();

        //calculam determinantul
        delta = (q.x-p.x)*(r.y-p.y) - (q.y - p.y) * (r.x-p.x);

        if (delta == 0) cout << "TOUCH\n";
        else {if (delta < 0) cout << "RIGHT\n";
        else cout << "LEFT\n"; }
    }

    return 0;
}
