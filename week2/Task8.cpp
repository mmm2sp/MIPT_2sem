#include <iostream>

using namespace std;

/*
 * Read HEX и сложить
 */

unsigned long long give_num_hex() {
    char c;
    unsigned long long final_num = 0;
    do {
        c = cin.get();
        if (c >= '0' && c <= '9') {
            final_num *= 16;
            final_num += (int) (c - '0');
        }
        else if (c >= 'A' && c <= 'F'){
            final_num *= 16;
            final_num += 10;
            final_num += (int) (c - 'A');
        }
    } while (c != '\n');
    return final_num;
}

int main(int argc, char **argv) {
    cout << "Enter 1st HEX number" << endl;
    auto num_1 = give_num_hex();
    cout << "Enter 2nd HEX number" << endl;
    auto num_2 = give_num_hex();
    cout << num_1 + num_2 << endl;
    return 0;
}
