#include <iostream>

using namespace std;

int main() {
    int x, y;
    double res = 1;
    cin >> x;
    cin >> y;

    if (y >= 0)
        for (int i = 0; i < y; i++)
            res *= x;
    else
        for (int i = 0; i < abs(y); i++)
            res /= x;

    cout << res << endl;

    return 0;
}
