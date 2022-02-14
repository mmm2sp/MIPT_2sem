#include <iostream>
using namespace std;

void print(char const* prefix, int v, char const* suffix); //define function

//int num = 10; // global variable

int fuct(int n){
    if (n == 1){
        return 1;
    }
    int nr = n * fuct(n - 1);
    return nr;
}

int main(int argc, char** argv) {
    int num;
    cin >> num;
    int res = fuct(num);
    print("Answer", res, "");
    return 0;
}

void print(char const* prefix, int v, char const* suffix){
    cout << prefix << ' ' << v << ' ' << suffix << endl;
}
