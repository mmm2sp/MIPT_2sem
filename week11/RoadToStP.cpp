#include <iostream>
#include <cstring>

using namespace std;

//дан массив координат заправок, размер бака (в км)
//вернуть массив координат использованных заправок (должно быть минимальное число)

int *solution(unsigned int max_distance, int distance, unsigned int N, int* data){
    /*
     * Args:
     * max_distance - размер бака в км
     * distance - расстояние до СПб в км
     * N - длина массива заправок
     * data[N] - отсортированный массив координат заправок
     *
     * Returns:
     * solution - массив длины solution[0]+1
     */
    bool flag = true;
    int coord = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    auto raw_answer = new int [N];
    while(coord <= distance - max_distance){
        while (data[i] <= coord + max_distance){
            flag = true;
            i++;
        }
        if(flag == false) return nullptr;
        coord = data[i-1];
        raw_answer[j] = coord;
        j++;
        flag = false;
    }
    auto answer = new int[j];
    answer[0] = j;
    for (i = 1; i <= j; ++i) {
        answer[i] = raw_answer[i-1];
    }
    delete [] raw_answer;
    return answer;
}

int main() {
    int distance; //координата СПб. Начальная координата (точки старта) - нуль
    cin >> distance;
    unsigned int N;
    cin >> N;
    auto data = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> data[i];
    }
    unsigned int max_distance;
    cin >> max_distance;
    auto answer = solution(max_distance, distance, N, data);
    if(answer != nullptr) {
        for (int i = 1; i <= answer[0]; ++i) cout << answer[i] << endl;
    }
    else cout << "No solution";
    return 0;
}
