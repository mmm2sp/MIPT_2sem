#include <iostream>
#include <cassert>

using namespace std;

/*
 * Печать числа в двоичном виде
 */

void print_binary(unsigned long long value) {
    if (value > 1){
        print_binary(value / 2);
    }
    cout << value % 2;
}

int main(int argc, char **argv) {
    unsigned long long num = 0;
    cout << "Enter DEC number" << endl;
    cin >> num;
    print_binary(num);
    cout << endl;
    return 0;
}
