#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

bool flag = false;

/*
 * Функция next_prime c возможностью сброса и тестированием
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
    if (flag == true){
        p = 2;
        flag = false;
    }
    while (number_is_prime(p) == false) p++;
    return p++;
}

void restart(){
    flag = true;
}


int main(int argc, char **argv) {
    assert(next_prime() == 2);
    assert(next_prime() == 3);
    assert(next_prime() == 5);
    restart();

    cout << "Enter number of primes:" << endl;
    int N;
    cin >> N;
    cout << "Your primes are:" << endl;
    for(int i = 0; i < N; i++) {
        auto prime = next_prime();
        cout << prime << ' ';
    }
    cout << endl;

    restart();
    auto prime = next_prime();
    cout << prime << ' ';


    return 0;
}
