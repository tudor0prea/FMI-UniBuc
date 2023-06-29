#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


/*
 * IDEEA:
 * daca dreapta este paralela cu axa Ox, intervalul pe axa x este actualizat in funcție de semnul coeficientului a.
 * daca dreapta este paralela cu axa Oy, intervalul pe axa y este actualizat in funcție de semnul coeficientului b.
 * apoi se verifica dacă coordonatele dreptunghiului se afla în intervalele calculate si se afiseaza raspunsul corespunzator.
 *
 */
int main() {
    int n;
    cin >> n;
    vector<vector<double>> plane;
    while (n--) {
        vector<double> p(3);
        for (int i = 0; i <= 2; ++i) {
            cin >> p[i];
        }
        plane.push_back(p);
    }
    int m;
    cin >> m;
    while (m--) {
        double x, y;
        cin >> x >> y;
        double min_x = INFINITY;
        double max_x = -INFINITY;
        double min_y = INFINITY;
        double max_y = -INFINITY;
        //incercam sa punem punctul intr-un dreptunghi
        //adica in cel mai mic

        for (const auto& p : plane) {
            double a = p[0], b = p[1], c = p[2];
            //plan vertical
            if (b == 0) {
                double mx=-c/a;
                if(a>0)
                     {if(mx>x&& mx<min_x) min_x=mx;}
                else if(mx<x && mx>max_x) max_x=mx;
            }
            //plan orizontal
            else if (a == 0) {
                    double my=-c/b;
                    if(b>0)
                        {if (my>y && my<min_y) min_y=my;}
                    else if(my<y && my>max_y) max_y=my;
            }
        }

        //vedem daca punctul se afla sau nu in dreptunghiul definit de
        //acele plane

            if (!(min_x == INFINITY || max_x == -INFINITY   || min_y == INFINITY  || max_y == -INFINITY )) {
                cout << "YES" << endl;
                //daca da, ii calculam si aria
                double arie= (max_x - min_x) * (max_y - min_y);
                printf("%.6f", arie);
                cout<<endl;
            } else {
                cout << "NO" << endl;
            }

    }
    return 0;
}