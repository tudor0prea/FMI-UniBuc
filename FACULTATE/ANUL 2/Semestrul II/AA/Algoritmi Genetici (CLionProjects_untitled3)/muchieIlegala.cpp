#include <iostream>
using namespace std;

// 8/10
// am folosit criteriul numeric



// creem imaginar punctul S este un punct imaginat, care este definit astfel: S este un punct în planul
// triunghiului ABC care are aceeași coordonată y ca și punctul D și aceeași coordonată x ca și punctul A.

// calculam aria celor doua paralelograme definite de vectorii AB si AC si respectiv AD si AS.
// aceste arii sunt calculate utilizand produsul vectorial

double critNum(int a[], int b[], int c[], int d[]) {
    double diag_p = (b[0] - a[0]) * (c[1] - a[1]) * (d[0] * d[0] + d[1] * d[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea diagonalei P a paralelogramului definit de AB si AC

    double p1 = (c[0] - a[0]) * (d[1] - a[1]) * (b[0] * b[0] + b[1] * b[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea primei laturi a paralelogramului definit de AC si AD

    double p2 = (d[0] - a[0]) * (b[1] - a[1]) * (c[0] * c[0] + c[1] * c[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea celei de-a doua laturi a paralelogramului definit de AD si AB

    double diag_s = (d[0] - a[0]) * (c[1] - a[1]) * (b[0] * b[0] + b[1] * b[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea diagonalei S a paralelogramului definit de AD si AS

    double s1 = (c[0] - a[0]) * (b[1] - a[1]) * (d[0] * d[0] + d[1] * d[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea primei laturi a paralelogramului definit de AS si BC

    double s2 = (d[1] - a[1]) * (b[0] - a[0]) * (c[0] * c[0] + c[1] * c[1] - a[0] * a[0] - a[1] * a[1]);
    //lungimea celei de-a doua laturi a paralelogramului definit de BC si AD

    return - (diag_p + p1 + p2 - diag_s - s1 - s2);
}

int main() {
    //am retinut punctele ca vectori de 2 elemente
    int a[2], b[2], c[2], d[2];
    cin >> a[0] >> a[1];
    cin >> b[0] >> b[1];
    cin >> c[0] >> c[1];
    cin >> d[0] >> d[1];

    cout << "AC: ";
    if (critNum(a, b, c, d) > 0) {
        cout << "ILLEGAL" << endl;
    } else {
        cout << "LEGAL" << endl;
    }

    cout << "BD: ";
    if (critNum(b, c, d, a) > 0) {
        cout << "ILLEGAL" << endl;
    } else {
        cout << "LEGAL" << endl;
    }

    return 0;
}
