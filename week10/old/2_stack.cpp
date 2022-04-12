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

struct forward_list {
    list_data data;
    forward_list *next;
};

struct stack {
    void push(list_data note) {
        auto node = new forward_list;
        node->data = note;
        node->next = top;
        top = node;
    }

    list_data pop() {
        auto note = top->data;
        auto top_old = top;
        top = top->next;
        delete top_old;
        return note;
    }

    forward_list *top;
};


forward_list *create_node(list_data data) {
    auto node = new forward_list;
    node->data = data; //(*node).data
    node->next = nullptr;
    return node;
}

void print_list(forward_list const *head) {
    auto it = head;
    while (it != nullptr) {
        cout << it->data.name << " " << it->data.dvalue << endl;
        it = it->next;
    }
}

int main() {
    stack *stk = new stack;
    stk->top = nullptr;

    print_list(stk->top);
    cout << "-------------------\n";
    stk->push({"Pi", 3.14});
    print_list(stk->top);
    cout << "-------------------\n";
    stk->push({"E", 2.7});
    print_list(stk->top);
    cout << "-------------------\n";
    auto note = stk->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(stk->top);
    cout << "-------------------\n";
    stk->push({"E", 2.7});
    print_list(stk->top);
    return 0;
}
