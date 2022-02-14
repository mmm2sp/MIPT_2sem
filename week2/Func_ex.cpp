#include <iostream>
using namespace std;

void print(char const* prefix, int v, char const* suffix); //define function

int num = 10; // global variable

int main(int argc, char** argv) {
    print("Global variable num is", num, "It is good!");
    return 0;
}

void print(char const* prefix, int v, char const* suffix){
    /*
     * This is document-string
     * We have to write it in big functions
     */
    static int alpha = 0; // init would be made only 1 time
    cout << prefix << ' ' << v << ' ' << suffix << endl;
}
