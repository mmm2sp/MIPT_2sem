#include <iostream>

using namespace std;

int main() {
    long max_num, max_mod;
    long num;

    while (cin >> num) {
        if (num % 101 == max_mod && num > max_num)
            max_num = num;
        if (num % 101 > max_mod) {
            max_mod = num % 101;
            max_num = num;
        }
    }
    cout << max_num << endl;
    return 0;
}
