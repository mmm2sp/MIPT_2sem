#include <iostream>
#include <cassert>

using namespace std;

/*
 * Факториал <= 20 unsigned long long
 */

unsigned long long fuct(int n){
    if (n == 1) return 1;
    auto nr = n * fuct(n - 1);
    return nr;
}

int main(int argc, char** argv) {
    assert(fuct(1) == 1);
    assert(fuct(2) == 2);
    assert(fuct(3) == 6);
    assert(fuct(10) == 3628800);
    assert(fuct(17) == 355687428096000);

    int num;
    cin >> num;
    auto res = fuct(num);
    cout << res << endl;
    return 0;
}
