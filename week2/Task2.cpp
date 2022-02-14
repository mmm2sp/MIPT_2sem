#include <iostream>

using namespace std;

/*
 * Чтение чисел с символами 12а3р3@ -> 1233
 */

unsigned long long give_num() {
    char c;
    unsigned long long final_num = 0;
    do {
        cin >> c;
        if (c >= '0' && c <= '9') {
            final_num *= 10;
            final_num += (int) (c - '0');
        }
    } while (c != '@');
    return final_num;
}


int main(int argc, char **argv) {
    auto final_num = give_num();
    cout << final_num << endl;
    return 0;
}
