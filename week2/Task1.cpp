#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

/*
 * Определить, простое ли число
 */

bool number_is_prime(unsigned long long n) {
    if (n == 1) return false;
    bool is_prime = true;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) is_prime = false;
    }
    return is_prime;
}

int main(int argc, char **argv) {
    assert(number_is_prime(1) == false);
    assert(number_is_prime(2) == true);
    assert(number_is_prime(3) == true);
    assert(number_is_prime(169) == false);
    assert(number_is_prime(239) == true);

    unsigned long long n;
    cin >> n;
    auto answer = number_is_prime(n);
    cout << answer << endl;
    return 0;
}
