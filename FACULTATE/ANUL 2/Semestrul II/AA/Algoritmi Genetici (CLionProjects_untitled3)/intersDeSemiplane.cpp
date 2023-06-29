#include <iostream>
#include <fstream>
#include <tuple>
//10
using namespace std;
int main() {

    int n;
    cin >> n;

    tuple<float, float, float> *semiplane = new tuple<float, float, float>[n];

    for (int i = 1; i <= n; i++) {
        float a, b, c;
        cin >> a >> b >> c;
        semiplane[i] = make_tuple(a, b, c);
    }

    float y_min = -10000000;
    float x_min = -10000000;
    float y_max = 10000000;
    float x_max = 10000000;


    //parcurgem semiplanele verficam pentru fiecare daca intersectia este o linie
    //paralela cu una din axe, caz in care se modifica
    //y_min sau y_max pentru semiplanele orizontale si x_min sau x_max pentru semiplanele verticale.

    for (int i = 1; i <= n; i++) {
        float a, b, c;
        tie(a, b, c) = semiplane[i];
        // float a = get<0>(semiplane[i]);
        // float b = get<1>(semiplane[i]);
        // float c = get<2>(semiplane[i]);
        //plan orizontal
        if (a == 0) {
            if (b < 0) {
                y_min = max(y_min, -c/b);
            } else {
                y_max = min(y_max, -c/b);
            }
        } //plan vertical
         else {
            if (a < 0) {
                x_min = max(x_min, -c/a);
            } else {
                x_max = min(x_max, -c/a);
            }
        }
    }

    if (x_min > x_max || y_min > y_max) {
        cout << "VOID\n";
    } else if (x_min != -10000000 && y_min != -10000000 &&
               x_max != 10000000 && y_max != 10000000) {
        cout << "BOUNDED\n";
    } else {
        cout << "UNBOUNDED\n";
    }

    delete[] semiplane;
    return 0;
}
