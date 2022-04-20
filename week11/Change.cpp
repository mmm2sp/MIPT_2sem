#include <iostream>

using namespace std;

//разменять заданную сумму монетами номиналом 1, 2, 5, 7, 10

int change(int sum, unsigned int num_coins, const int* coins, int* memorization){
    if(memorization[sum] != -1) return memorization[sum];
    int min_number = sum + 1;
    for (int i = 0; i < num_coins; ++i) {
        if(sum >= coins[i]) {
            min_number = min(min_number, change(sum - coins[i], num_coins, coins, memorization));
        } else break;
    }
    memorization[sum] = min_number + 1;
    return min_number + 1;
}

void cout_change(int sum, unsigned int num_coins, const int* coins, int* memorization){
    if (sum <= 0) return;
    for (int i = 0; i < num_coins; ++i) {
        if ((sum >= coins[i]) && (memorization[sum - coins[i]] == memorization[sum] - 1) ){
            cout << coins[i] << " ";
            sum -= coins[i];
            break;
        }
    }
    cout_change(sum, num_coins, coins, memorization);
}

void find_change(int sum, unsigned int num_coins, const int* coins){
    if (sum < 0) return;
    auto memorization = new int[sum+1];
    memorization[0] = 0;
    for (int i = 1; i < sum + 1; ++i) {
        memorization[i] = -1;
    }
    cout << change(sum, num_coins, coins, memorization) << endl;
    cout_change(sum, num_coins, coins, memorization);
    delete [] memorization;
}

int main() {
    int x;
    cin >> x;
    auto coins = new int[5] {1, 2, 5, 7, 10};
    find_change(x, 5, coins);
    delete [] coins;
    return 0;
}
