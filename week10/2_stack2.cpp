#include <iostream>

using namespace std;

struct list_data {
    const char *name;
    double dvalue;
};

struct forward_list {
    list_data data;
    forward_list *next;
};

struct stack {
public:
    void push(list_data note) {
        auto node = new forward_list;
        node->data = note;
        node->next = top;
        top = node;
    }

    list_data pop() {
        if(top == nullptr) return {"__empty__", 0};
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

void print_list(forward_list const *head) {
    auto it = head;
    while (it != nullptr) {
        cout << it->data.name << " " << it->data.dvalue << endl;
        it = it->next;
    }
}

int main() {
    stack *stk = new stack;

    print_list(stk->head());
    cout << "-------------------\n";
    stk->push({"Pi", 3.14});
    print_list(stk->head());
    cout << "-------------------\n";
    stk->push({"E", 2.7});
    print_list(stk->head());
    cout << "-------------------\n";
    auto note = stk->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(stk->head());
    cout << "-------------------\n";
    note = stk->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(stk->head());
    cout << "-------------------\n";
    note = stk->pop();
    cout << "EXIT " << note.name << " " << note.dvalue << endl;
    cout << "-------------------\n";
    print_list(stk->head());
    cout << "-------------------\n";
    stk->push({"E", 2.7});
    print_list(stk->head());
    return 0;
}
