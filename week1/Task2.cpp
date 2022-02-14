#include <iostream>

using namespace std;

int main() {
    int N;
    char sign = 'a';
    cin >> N;

    if (N % 5 == 0)
        sign = '@';
    else
        sign = '%';
    for (int i = 0; i < N; i++)
        cout << sign;
    cout << endl;

    return 0;
}
