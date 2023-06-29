#include <iostream>
#include <cmath>
//10
using namespace std;


double dist(pair<double, double> P1, pair<double, double> P2) {
    return sqrt(pow(P1.first - P2.first, 2) + pow(P1.second - P2.second, 2));
}

double calc_area(pair<double, double> A, pair<double, double> B, pair<double, double> C) {
    return abs((A.first * (B.second - C.second) + B.first * (C.second - A.second) + C.first * (A.second - B.second)) / 2.0);
}

string pozitie_relativa(pair<double, double> P, pair<double, double> A, pair<double, double> B, pair<double, double> C) {
    double a = dist(A, B);
    double b = dist(B, C);
    double c = dist(C, A);
    double Aria = calc_area(A, B, C);
    double r = (a * b * c) / (4 * Aria);

    double xA = A.first, yA = A.second;
    double xB = B.first, yB = B.second;
    double xC = C.first, yC = C.second;
    double xP = P.first, yP = P.second;

    //calculam distanta dintre punctul P si centrul cercului
    double D = 2.0 * (xA * (yB - yC) + xB * (yC - yA) + xC * (yA - yB));
    double x = ((xA * xA + yA * yA) * (yB - yC) + (xB * xB + yB * yB) * (yC - yA) + (xC * xC + yC * yC) * (yA - yB)) / D;
    double y = ((xA * xA + yA * yA) * (xC - xB) + (xB * xB + yB * yB) * (xA - xC) + (xC * xC + yC * yC) * (xB - xA)) / D;
    double d = sqrt(pow((x - xP), 2) + pow((y - yP), 2));

    //determinam pozitia relativa a punctului P fata de cercul circumscris
    if (d < r) {
        return "INSIDE\n";
    } else if (d > r) {
        return "OUTSIDE\n";
    } else {
        return "BOUNDARY\n";
    }
}

int main() {
    int n, x, y;

    cin>>x>>y;

    pair<double, double> A(x, y);

    cin>>x>>y;
    pair<double, double> B(x, y);

    cin>>x>>y;
    pair<double, double> C(x, y);



    cin>>n;
    for(int i=1;i<=n;i++) {

        cin >> x >> y;


        pair<double, double> P(x, y);

        cout << pozitie_relativa(P, A, B, C);
    }
    return 0;
}
