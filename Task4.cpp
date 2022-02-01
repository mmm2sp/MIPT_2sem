#include <iostream>

using namespace std;

int main() {

    int N, number, max_number;
    cin >> N;
    cin >> max_number;
    for (int i = 1; i < N; i++) {
        cin >> number;
        if (number > max_number)
            max_number = number;
    }
    cout << max_number << endl;
    return 0;
}
