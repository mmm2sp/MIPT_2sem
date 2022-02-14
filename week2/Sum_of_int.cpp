#include <iostream>
using namespace std;

void print_int(int number){
    cout << "Sum of 2 int numbers is " << number << endl;
}

int read_int(){
    int value;
    cin >> value;
    return value;
}

int sum_of_int(int lhc, int rhc){
    return lhc+rhc;
}

int main(int argc, char** argv) {
    int a = read_int();
    auto b = read_int();
    auto c = sum_of_int(a, b);
    print_int(c);
    return 0;
}
