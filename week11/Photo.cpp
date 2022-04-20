#include <iostream>

using namespace std;

//дан массив времен начала и конца времени обеда для каждой синички
//вернуть массив времен, когда надо приходить, чтобы сфоткть всех синичек, сделав минимальное число кадров
struct segment{
    int begin = 0;
    int end = 0;
};

struct forward_list {
    segment data;
    forward_list *next = nullptr;
};

struct stack {
public:
    void push(segment note) {
        auto node = new forward_list;
        node->data = note;
        node->next = top;
        top = node;
    }

    segment pop() {
        if(top == nullptr) return {0, 0};
        auto note = top->data;
        auto top_old = top;
        top = top->next;
        delete top_old;
        return note;
    }

    forward_list *head() {
        return top;
    }

private:
    forward_list *top = nullptr;
};

bool comp(segment a, segment b){
    if(a.end > b.end) return true;
    else return false;
}

int *solution(unsigned int N, segment *data){
    //сортируем по времени окончания обеда каждой птички
    auto stk = new stack;
    for (int i = 0; i < N; ++i) {
        stk->push(data[i]);
    }
    int* answer = new int [N+1];
    auto head = stk->head();
    int time;
    forward_list* ptr;
    forward_list* tmp;
    int i = 0;

    while(head != nullptr) {
        time = (head->data).end;
        ptr = head;
        answer[i] = time;
        while (ptr != nullptr) {
            tmp = ptr->next;
            if (tmp != nullptr && tmp->data.begin <= time) {
                ptr->next = tmp->next;
                delete tmp;
            }
            ptr = ptr->next;
        }
        stk->pop();
        head = stk->head();
        i++;
    }
    answer[N] = i;
    delete stk;
    return answer;
}


int main() {
    unsigned int N;
    cin >> N;
    auto data_0 = new segment[N];
    for (int i = 0; i < N; ++i) {
        cin >> data_0[i].begin;
        cin >> data_0[i].end;
    }
    sort(data_0, data_0 + N, comp);

    for (int i = 0; i < N; ++i) {
        cout << data_0[i].begin << " ";
        cout << data_0[i].end << endl;
    }
    cout <<"---" << endl;

    auto answer = solution(N, data_0);

    for (int i = 0; i < answer[N]; ++i) {
        cout << answer[i] << " ";
    }

    delete[] answer;

    return 0;
}
