#include <iostream>

using namespace std;

int main() {
    long old_num, num, len = 1, max_len = 1;
    bool first_num = true;
    while (cin >> num) {
        if (first_num == true)
            first_num = false;
        else {
            if (num >= old_num)
                len++;
            else {
                if (len > max_len)
                    max_len = len;
                len = 1;
            }
        }
        old_num = num;
    }
    if (len > max_len)
        max_len = len;
    cout << max_len << endl;
    return 0;
}
