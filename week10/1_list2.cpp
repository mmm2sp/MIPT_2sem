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

bool equal(list_data const &left, list_data const &right){
  return left.dvalue == right.dvalue && strcmp(left.name, right.name) == 0;
}

void free_data(list_data &data){
  //
}

list *create_node(list_data data) {
  auto node = new list;
  node->data = data; //(*node).data
  node->next = nullptr;
  node->previous = nullptr;
  return node;
}

list *insert_front(list *head, list *node) {
  node->next = head;
  if(head != nullptr) head->previous = node;
  return node;
}

list *insert(list *previous, list *node, list *next) {
  if (previous == nullptr) {
      return insert_front(previous, node);
  }

  if (next == nullptr) {
      previous->next = node;
      node->previous = previous;
      return node;
  }

  node->next = previous->next;
  node->previous = next->previous;

  previous->next = node;
  next->previous = node;

  return node;
}

list *insert_after(list *after, list* node){
    return insert(after, node, after->next);
}

list *insert_before(list *before, list* node){
    return insert(before->previous, node, before);
}

list* find(list* head, list_data data){
  auto it = head;
  while (it != nullptr && !equal(it->data, data)){
    it = it->next;
  }
  return it;
}

void print_list(list const *head) {
  auto it = head;
  while (it != nullptr) {
    cout << it->data.name << " " << it->data.dvalue << endl;
    it = it->next;
  }
}

list* delete_node(list *head, list *node){
  if (head == node){
    auto next_head = head->next;
    free_data(node->data);
    delete node;
    return next_head;
  }

  auto it = head;
  while (it != nullptr && it->next != node){
    it = it->next;
  }
  if (it == nullptr){
    cerr << "Wrong node for delete!\n";
    exit(-10);
  }
  it->next = node->next;
  (it->next)->previous = it;

  free_data(node->data);
  delete node;
  return head;
}

int main() {
  list *head = nullptr;

  auto node_1 = create_node({"Pi", 3.14});
  auto node_2 = create_node({"E", 2.7});

  head = insert_front(head, node_2);
  head = insert_front(head, node_1);

  auto node_3 = create_node({"g", 9.8});
  insert_after(node_1, node_3);

  auto node_4 = create_node({"hbar", 6.63e-31});
  insert_before(node_3, node_4);

  print_list(head);

  auto res = find(head, {"hbar", 6.63e-31});
  delete_node(head, res);

  cout << "-------------------\n";
  print_list(head);

  while (head != nullptr)
    head = delete_node(head, head);

  cout << "-------------------\n";
  print_list(head);
  return 0;
}
