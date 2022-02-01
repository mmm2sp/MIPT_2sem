#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    if (N % 5 == 0) {
        cout << "@@@@@" << endl;
    } else {
        cout << N % 5 << endl;
    }

    return 0;
}
