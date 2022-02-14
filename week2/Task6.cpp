#include <iostream>
#include <cassert>

using namespace std;

/*
 * Фибоначчи <= 50 unsigned long long
 */

unsigned long long fib(unsigned int n){
    if (n < 3) return 1;
    unsigned long long num_2 = 1, num_1 = 1; // (i-1)й и (i-2)й элементы поледовательности Фибоначчи
    for (int i = 2; i < n; i++){
        num_1 += num_2; // теперь тут лежит iй
        num_2 = num_1 - num_2; // а здесь (i-1)й
    }
    return num_1;
}

int main(int argc, char** argv) {
    assert(fib(1) == 1);
    assert(fib(2) == 1);
    assert(fib(5) == 5);
    assert(fib(25) == 75025);
    assert(fib(50) == 12586269025);

    int num;
    cin >> num;
    auto res = fib(num);
    cout << res << endl;
    return 0;
}
