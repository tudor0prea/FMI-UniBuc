#include <iostream>
#include <math.h>
using namespace std;

// testare nr prime
// se dau a si b => nr prime [a,b]
int main()
{
    int a, b, n, i;
    cin >> a >> b;
    if (a < b)
    {
        for (n= a; n <= b; n++)
        {
            if (n % 2 == 0)
                i=n;
            else
            {
                i = 3;
                while (i <= sqrt(n))
                {
                    if (n % i == 0)
                        i = n;
                    else
                        i = i + 2;
                }

                if (i != n)
                    cout << n << " ";

            }
        }
    }
    else
        cout << a << " si " << b << " nu formeaza un interval"<< endl;

        return 0;

    }