#include <iostream>

using namespace std;

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
public:
    void push(list_data note) {

        list* node = new list;
        if(top != nullptr) top->previous = node;
        node->data = note;
        node->next = top;
        node->previous = nullptr;
        top = node;
        if(bottom == nullptr){
            bottom = top;
        }
    }

    list_data pop() {
        if(bottom == nullptr) return {"__empty__", 0};
        auto note = bottom->data;
        auto it = bottom;
        if(bottom->previous != nullptr){
            bottom = bottom->previous;
            bottom->next = nullptr;
        }
        else{
            top = nullptr;
            bottom = nullptr;
        }
        delete it;
        return note;
    }

    list *head(){
        return top;
    }

private:
    list *top = nullptr;
    list *bottom = nullptr;
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

    print_list(que->head());
    cout << "-------------------\n";
    que->push({"Pi", 3.14});
    print_list(que->head());
    cout << "-------------------\n";
    que->push({"E", 2.7});
    print_list(que->head());
    cout << "-------------------\n";
    auto note = que->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(que->head());
    cout << "-------------------\n";
    note = que->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(que->head());
    cout << "-------------------\n";
    note = que->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(que->head());
    cout << "-------------------\n";
    que->push({"E", 2.7});
    print_list(que->head());
    return 0;
}
