#include <iostream>
#include <cmath>

using namespace std;

/*
 * Функция next_prime
 */

bool number_is_prime(unsigned long long n) {
    if (n == 1) return false;
    bool is_prime = true;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) is_prime = false;
    }
    return is_prime;
}

int next_prime() {
    static int p = 2;
    while (number_is_prime(p) == false){
        p++;
    }
    return p++;
}


int main(int argc, char **argv) {
    cout << "Enter number of primes:" << endl;
    int N;
    cin >> N;
    cout << "Your primes are:" << endl;
    for(int i = 0; i < N; i++) {
        auto prime = next_prime();
        cout << prime << ' ';
    }
    return 0;
}
