#include <iostream>
#include <cmath>
#include <cassert>

/*
 * Молекулярная динамика
 * Вз-ие  в некотором конечном радиусе
 * Списки ближайших соседей
 *
 * Задание:
 * функция принимает список всех частиц
 * Массив: для каждой частицы свой список ближайших (в радиусе R) частиц + линейный массив с размером
 *
 *
 * ###############
 * #########################
 * #####
 * ##############
 * #######
 *
 *
 * 15
 * 25
 * 5
 * 14
 * 7
 * */


using namespace std;

void neib(double **coords, long N, double R, long **data, long *len) {
    /*
     * Args:
     *     coords - указатель на начало двумерного массива с координатами для каждой частицы
     *     N - число частиц
     *     R - радиус вз-ия
     * Returns:
     *     data - указатель на начало двумерного массива с номерами ближайших ячеек для каждой i из N
     *     len - указатель на начало массива с длинами массивов data[i]
     */
    long ** arr = new long* [N]; // Временный массив
    for (long i = 0; i < N; i++) {
        len[i] = 0;
        arr[i] = new long [N];
    }

    for (long i = 0; i < N; i++) {
        for (long j = i + 1; j < N; j++) {
            if (sqrt(pow((coords[i][0] - coords[j][0]), 2) + pow((coords[i][1] - coords[j][1]), 2)) < R) {
                arr[i][len[i]] = j;
                arr[j][len[j]] = i;
                len[j]++;
                len[i]++;
            }

        }
    }
    for (long i = 0; i < N; i++) {
        data[i] = new long [len[i]];
        for (long j = 0; j < len[i]; j++)
        data[i][j] = arr[i][j];
    }

    for (long i = 0; i < N; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main() {
    long N = 100;
    double ** coord = new double* [N];
    for (long i = 0; i < N; i++) {
        coord[i] = new double [2];
        coord[i][0] = i % 10;
        coord[i][1] = i / 10;
    }

    long ** data = new long* [N];
    long * len = new long [N];
    neib(coord, N, 1.1, data, len);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < len[i]; j++){
            cout << '(' << coord[data[i][j]][0] << ", " << coord[data[i][j]][1] << ") ";
        }
        cout << endl;
    }

    return 0;
}