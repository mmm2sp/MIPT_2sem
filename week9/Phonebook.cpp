/*
 * Телефонный справочник. Программа должна иметь возможность каким-то образом хранить в себе набор записей вида:
 * name tel email
 * И выполнять запросы поиска записей по имени и по номеру.
 */

#include <iostream>
#include <cmath>

using namespace std;

struct Info{
    string name;
    unsigned long long phone;
    string mail;
};

Info find_info(string name, Info* PhoneBook, unsigned long len_book){
    for (unsigned long i = 0; i < len_book; ++i) {
        if(name == PhoneBook[i].name) return PhoneBook[i];
    }
    Info answer = {"__null__", 0, "__null__"};
    return answer;
}

Info find_info(unsigned long long phone, Info* PhoneBook, unsigned long len_book){
    for (unsigned long i = 0; i < len_book; ++i) {
        if(phone == PhoneBook[i].phone) return PhoneBook[i];
    }
    Info answer = {"__null__", 0, "__null__"};
    return answer;
}

void print(Info data){
    cout << data.name << ' ' << data.phone << ' ' << data.mail << endl;
}

int main() {
    Info *PhoneBook = new Info[10000];
    for (unsigned long i = 0; i < 10000; ++i) {
        auto str = to_string(i);
        PhoneBook[i] = {"name" + str, i, "adr" + str};
    }
    auto Vasya = find_info(1234, PhoneBook, 10000);
    print(Vasya);
    auto Petya = find_info("name1111", PhoneBook, 10000);
    print(Petya);
    return 0;
}
