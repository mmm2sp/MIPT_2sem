#include <iostream>

using namespace std;

/* Даны стоимости ночевки в хостелах вдоль дороги Москва-Владивосток.
 * Хостелы расположены через каждые 500 км. За один день вы можете проехать либо 500 км, либо 1000 км.
 * Необходимо определить минимальную стоимость путешествия и вывести порядковые номера хостелов,
 * в которых необходимо остановиться, а также их стоимость.
 */


void solution(unsigned int dist, int* price){
    auto full_price = new int[dist+1];
    int* previous_stop = new int [dist+1];

    full_price[0] = price[0];
    previous_stop[0] = -1;
    full_price[1] = price[1];
    previous_stop[1] = 0;

    for (int i = 2; i <= dist; ++i) {
        full_price[i] = price[i] + min(full_price[i-2], full_price[i-1]);
        if (full_price[i-2] < full_price[i-1]){
            full_price[i] = price[i] + full_price[i-2];
            previous_stop[i] = i - 2;
        }
        else{
            full_price[i] = price[i] + full_price[i-1];
            previous_stop[i] = i - 1;
        }
    }
    cout << "Minimal cost is " << full_price[dist] << endl;\

    cout << "Hostels' numbers are ";
    int host_num = dist;
    while(host_num > 0){
        cout << host_num << " ";
        host_num = previous_stop[host_num];
    }
    cout << endl;

    cout << "Hostels' prices are ";
    host_num = dist;
    while(host_num > 0){
        cout << price[host_num] << " ";
        host_num = previous_stop[host_num];
    }
    cout << endl;

    delete [] full_price;
    delete [] previous_stop;
}

int main() {
    unsigned int distance; //Расстояние до Владивостока в у.е. (1 у.е. = 500 км). Начальная координата (точки старта) - нуль
    cin >> distance;
    auto price = new int[distance + 1];
    price[0] = 0;
    for (int i = 1; i < distance; ++i) {
        cin >> price[i];
    }
    price[distance] = 0;
    solution(distance, price);
    delete [] price;
    return 0;
}
