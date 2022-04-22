#include <iostream>

using namespace std;


int **min_dist_lu(unsigned height, unsigned width, int** picture){
    //выполняет проход из левого верхнего угла
    auto answer = new int*[height];
    for (int i = 0; i < height; ++i) {
        answer[i] = new int[width];
    }

    for (int i = 0; i < height + width; ++i) {
        int j = 0;
        if (i >= height) j = i + 1 - height;
        while ((j <= i) && (j < width)) {
            if ((i-j == 0) || (j == 0)) answer[i-j][j] = 0;
            else {
                if ((picture[i - j][j] != picture[i - j - 1][j]) || (picture[i - j][j] != picture[i - j][j-1])) answer[i - j][j] = 0;
                else answer[i - j][j] = 1 + min(answer[i - j - 1][j], answer[i - j][j - 1]);
            }
            j++;
        }
    }
    return answer;
}

int **min_dist(unsigned height, unsigned width, int** picture){
    auto answer = new int**[4]; //для проходов из 4х углов
    for (int dir = 0; dir < 4; ++dir) {
        answer[dir] = new int*[height];
        for (int i = 0; i < height; ++i) {
            answer[dir][i] = new int[width];
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            answer[1][i][j] = picture[height - i - 1][j];
            answer[2][i][j] = picture[i][width - j - 1];
            answer[3][i][j] = picture[height - i - 1][width - j - 1];
        }
    }

    answer[0] = min_dist_lu(height, width, picture);

    answer[1] = min_dist_lu(height, width, answer[1]);
    answer[2] = min_dist_lu(height, width, answer[2]);
    answer[3] = min_dist_lu(height, width, answer[3]);


    auto ans = new int*[height];
    for (int i = 0; i < height; ++i) {
        ans[i] = new int[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            ans[i][j] = min(min(answer[0][i][j], answer[1][height - i - 1][j]),
                            min(answer[2][i][width - j - 1], answer[3][height - i - 1][width - j - 1]));
        }
    }

    for (int dir = 0; dir < 4; ++dir) {
        for (int i = 0; i < height; ++i) {
            delete [] answer[dir][i];
        }
        delete [] answer[dir];
    }
    delete [] answer;

    return ans;
}

void max_dist(unsigned height, unsigned width, int** picture) {
    auto res = min_dist(height, width, picture);
    cout << "color: y_max x_max :distance" << endl;
    cout << "c: y x :d" << endl;
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if(res[i][j] >= res[i-1][j] && res[i][j] >= res[i][j-1] &&
            res[i][j] >= res[i-1][j-1] && res[i][j] >= res[i+1][j+1] &&
            res[i][j] >= res[i+1][j-1] && res[i][j] >= res[i-1][j+1] &&
            res[i][j] >= res[i+1][j] && res[i][j] >= res[i][j+1]){
                cout << picture[i][j] << ": " << i << " " << j << " :" << res[i][j] << endl;
            }
        }
    }
    for (int i = 0; i < height; ++i) {
        delete[] res[i];
    }
    delete[] res;
}


int main() {
    unsigned M, N;
    cin >> M;
    cin >> N;
    auto data = new int*[M];

    for (int i = 0; i < M; ++i) {
        data[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            cin >> data[i][j];
        }
    }

    //обработка
    max_dist(M, N, data);

    for (int i = 0; i < M; ++i) {
        delete[] data[i];
    }
    delete[] data;

    return 0;
}
