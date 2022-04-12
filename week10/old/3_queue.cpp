#include <iostream>
#include <cstring>

using namespace std;
//  1. Create
//  2. insert
//    2.1 insert_front O(1)
//    2.2 insert_after O(1)
//    2.3 insert_before O(N)
//  3. delete O(N)
//  4. find O(N)

struct list_data {
    const char *name;
    double dvalue;
};

struct list {
    list_data data;
    list *next;
    list *previous;
};

struct queue {
    void push(list_data note) {
        list* node = new list;
        if(top != nullptr) top->previous = node;
        node->data = note;
        node->next = top;
        node->previous = nullptr;
        top = node;
    }

    list_data pop() {
        auto it = top;
        while(it->next != nullptr){
            it = it->next;
        }
        auto note = it->data;
        (it->previous)->next = nullptr;
        delete it;
        return note;
    }

    list *top;
};

void print_list(list const *head) {
    auto it = head;
    while (it != nullptr) {
        cout << it->data.name << " " << it->data.dvalue << endl;
        it = it->next;
    }
}

int main() {
    queue *que = new queue;
    que->top = nullptr;

    print_list(que->top);
    cout << "-------------------\n";
    que->push({"Pi", 3.14});
    print_list(que->top);
    cout << "-------------------\n";
    que->push({"E", 2.7});
    print_list(que->top);
    cout << "-------------------\n";
    auto note = que->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(que->top);
    cout << "-------------------\n";
    que->push({"E", 2.7});
    print_list(que->top);
    return 0;
}
