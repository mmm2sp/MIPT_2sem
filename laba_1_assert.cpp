#include <iostream>
#include <random>
#include <cassert>

using namespace std;

//global variables
const int LENGTH = 5; //Длина и ширина статического массива
unsigned int width, height;
unsigned int num_disl = 7;
unsigned int min_num_sim = 1000;
unsigned int max_num_sim = 10000;

/*
 * 0 -- нормальные кристаллы
 * +1 -- подвижные дислокации, прошедшие проверку, что они не 2
 * -1 -- подвижные дислокации, еще не прошедшие проверку, что они не 2
 * 2 -- неподвижные дислокации
 */

unsigned int rnd_width(){
    static mt19937_64 engine(random_device{}());
    uniform_int_distribution<int> uni (0, width - 1); //including a and b
    return abs(uni(engine));
}

unsigned int rnd_height(){
    static mt19937_64 engine(random_device{}());
    uniform_int_distribution<int> uni (0, height - 1); //including a and b
    return abs(uni(engine));
}

unsigned long long rnd_disl(){
    unsigned long long answer = rnd_width() + rnd_height() * width;
    return answer;
}

int rnd_shift(){
    static int num_start = 0;
    num_start++;
    if (num_start == 1) return(2);
    if (num_start == 2) return(1);
    if (num_start == 3) return(2);
    if (num_start == 4) return(2);
    if (num_start == 5) return(3);
    if (num_start == 6) return(1);

    static mt19937_64 engine(random_device{}());
    static uniform_int_distribution<int> uni (1, 4); //including 1 and 4
    return uni(engine);
}


int disl_shift(int cryst[LENGTH][LENGTH], int x, int y){
    /*
     * Проверяет, нет ли дислокации в клетке кристалла с указанными координатами
     * Если нет, создает и возвращает 0
     * Если есть, ничего не делает и возвращает 1
     */
    if (cryst[y][x] == 0){ // защита от попадания двух дислокаций попасть в одну клетку
        cryst[y][x] = -1;
        return 0;
    }
    return 1;
}

void shift(int cryst[LENGTH][LENGTH]){
    /*
     * Сдвиг всех подвижных дислокаций в случайном направлении
     * Сдвинутые дислокации отличаются знаком (-1). На этапе проверки check(...) знак снова станет +1
     */
    int move; //направление сдвига (1, 2, 3, 4) -> (вверх, вправо, влево, вниз)
    for (int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            if (cryst[j][i] == 1){
                move = rnd_shift(); // направление движения
                auto a = 0;
                if (move == 1) a = disl_shift(cryst, i, j - 1);
                if (move == 2) a = disl_shift(cryst, i + 1, j);
                if (move == 3) a = disl_shift(cryst, i, j + 1);
                if (move == 4) a = disl_shift(cryst, i - 1, j);
                cryst[j][i] *= -a; // Если сдвинулись, ноль, иначе все оставляем, как есть
            }
        }
    }
}

bool check(int cryst[LENGTH][LENGTH]) {
    /*
     * Проверка всех подвижных дислокаций на то, не остановились ли они
     */
    bool stop = true; //Считаем, что все дислокации остановились. Иначе потом поменяем
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (cryst[j][i] == -1) {
                //Проверка границы
                if (i == 0 || j == 0 || i == width || j == height) cryst[j][i] = 2;
                else { //Проверка соседей
                    if (cryst[j - 1][i] != 0 || cryst[j][i + 1] != 0 ||
                        cryst[j + 1][i] != 0 || cryst[j][i - 1] != 0) {
                        cryst[j][i] = 2;
                    }
                    else{ //Если не остановился
                        cryst[j][i] = 1;
                        if (stop) stop = false;
                    }
                }
            }
        }
    }
    return stop;
}

void pure_cryst(int crystal[LENGTH][LENGTH]){
    for (int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            crystal[j][i] = 0;
        }
    }
}

void generate_dislocations(int cryst[LENGTH][LENGTH]){
    unsigned long long n = 0; //number of created dislocations
    unsigned long long a; //new dislocation coordinate
    while(n < num_disl){ //пока не выберем num_disl элементов
        a = rnd_disl();
        if (cryst[a / width][a % width] != -1){
            cryst[a / width][a % width] = -1;
            n++;
        }
    }
    check(cryst);
}


bool step(int cryst[LENGTH][LENGTH]){
    /*
     * Полностью осуществляет одно действие над кристаллом
     */
    shift(cryst);
    auto finished = check(cryst);
    return finished;
}

unsigned long long simulation(int crystal[LENGTH][LENGTH]){
    /*
     * Выполняет сдвиги, пока все дислокации не остановятся
     * Возвращает длительность процесса (в шагах)
     */
    unsigned long long t = 0;
    bool finished = false;
    while (!finished){
        finished = step(crystal);
        t++;
    }
    return t;
}

unsigned long long simulate(int crystal[LENGTH][LENGTH]){
    /*
     * Запускает симуляцию num_sim раз
     * Возвращает среднюю длительность симуляции (в шагах)
     */
    unsigned long long duration = 0;
    auto num_sim = max(min_num_sim, max_num_sim * width * height / LENGTH / LENGTH);
    for (int i = 0; i < num_sim; i++){
        pure_cryst(crystal);
        generate_dislocations(crystal);
        duration += simulation(crystal);
    }
    duration = duration / num_sim;
    return duration;
}

///////////////////////////////////////////////

void print(int array[LENGTH][LENGTH]){
    /*
     * Печатает квадратный массив со стороной LENGTH
     */
    for (int j = 0; j < LENGTH; j++) {
        for (int i = 0; i < LENGTH; i++) {
            cout << array[j][i] << ", ";
        }
        cout << endl;
    }
}

void assert1 () {
    /*
     * Проверяет функцию generate_dislocations
     * Отражает работоспособность функций pure_cryst, check
     */
    int crystal[LENGTH][LENGTH] = {};
    for (int i = 1; i < LENGTH * LENGTH; i += LENGTH){
        num_disl = i;
        pure_cryst(crystal);
        generate_dislocations(crystal);
        cout << "num_disl = " << num_disl << " dislocations were created and checked" << endl;
        print(crystal);
    }
    cout << "-------end_of_assert1-------" << endl << endl;
}

void assert2 (){
    /*
     * Проверяет функции disl_shift и check
     * Отражает работоспособность функции shift
     */
    int crystal[LENGTH][LENGTH] = {{-1, 0, 0, 0, 0},
                                   {0, -1, 0, 0, 0},
                                   {0, 0, 0, -1, 0},
                                   {-1, 0, 0, 0, 0},
                                   {0, 0, 0, -1, 0}};
    cout << "Original crystal:" << endl;
    print(crystal);

    assert(disl_shift(crystal, 3, 2) == 1); //есть дислокация
    assert(disl_shift(crystal, 2, 1) == 0); //нет дислокации, добавляем
    assert(disl_shift(crystal, 1, 3) == 0); //нет дислокации, добавляем
    cout << "Crystal after 3 asserts of disl_shift:" << endl;
    print(crystal);

    assert(check(crystal) == false); //Останавливаем остановившиеся дислокации. Еще НЕ все остановились
    cout << "After check:" << endl;
    print(crystal);

    shift(crystal);
    cout << "After shift:" << endl;
    print(crystal);

    assert(check(crystal) == true); //Останавливаем остановившиеся дислокации. Все остановились
    cout << "After 2nd check:" << endl;
    print(crystal);

    cout << "-------end_of_assert2-------" << endl << endl;
}

void assert0 (){
    /*
     * Проверка на узкие места
     *
     */
    int crystal[LENGTH][LENGTH] = {{0, 0, 0, 0, 0},
                                   {0, 0, 1, 0, 0},
                                   {0, 0, 0, 1, 0},
                                   {0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0}};
    cout << "Original crystal:" << endl;
    print(crystal);

    shift(crystal);
    cout << "After shift:" << endl;
    print(crystal);

    assert(check(crystal) == true); //Останавливаем остановившиеся дислокации. Все остановились
    cout << "After check:" << endl;
    print(crystal);
    cout <<  endl;


    int cryst[LENGTH][LENGTH] = {{0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0},
                                   {0, 1, 0, 0, 0},
                                   {0, 0, 1, 0, 0},
                                   {0, 0, 0, 0, 0}};
    cout << "Original crystal 2:" << endl;
    print(cryst);

    shift(cryst);
    cout << "After shift:" << endl;
    print(cryst);

    assert(check(cryst) == false); //Останавливаем остановившиеся дислокации. НЕ остановились
    cout << "After check:" << endl;
    print(cryst);
    cout <<  endl;


    int cr[LENGTH][LENGTH] = {{0, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0},
                                 {0, 0, 0, 0, 0},
                                 {0, 0, 1, 0, 0},
                                 {0, 0, 0, 0, 0}};
    cout << "Original crystal 3:" << endl;
    print(cr);

    shift(cr);
    cout << "After shift:" << endl;
    print(cr);

    assert(check(cr) == true); //Останавливаем остановившиеся дислокации. НЕ остановились
    cout << "After check:" << endl;
    print(cr);

    cout << "-------end_of_assert0-------" << endl << endl;
}

int main() {
    width = LENGTH;
    height = LENGTH;
    assert0();
    assert1();
    assert2();


    return 0;
}
