/*
 * Дан список рецептов для различных предметов в формате:
 * ItemName subitem_count subitems[subitem_count] creation_cost
 *     ItemName – имя предмета, одна строка без пробелов
 *     subitem_count – количество предметов для сборки ItemName
 *     subitems[subitem_count] – список предметов из которых собирается ItemName, их количество равно subitem_count
 *     creation_cost – количество ресурсов (абстрактных) для создания предмета
 * Гарантируется, что рецепты существуют для всех предметов.
 * 2) Необходимо, имея имя предмета и набор рецептов для его создания определить стоимость этого предмета.
 * 3) Oпределить какое количество предметов ItemName можно создать имея TotalGold единиц ресурсов.
 */

#include <iostream>
#include <cmath>

using namespace std;

struct Recipe{
    string dish_name;
    unsigned int num_ingr;
    string *ingredients;
    int cost;
};

Recipe find_recipe(string name, Recipe* CookBook, unsigned int len_book){
    for (unsigned int i = 0; i < len_book; ++i) {
        if(name == CookBook[i].dish_name) return CookBook[i];
    }
    string *ingredients = new string[1] {"__null__"};
    Recipe answer = {"__null__", 1, ingredients, 0};
    return answer;
}

Recipe find_recipe(unsigned int num_ingr, string *ingredients, Recipe* CookBook, unsigned int len_book){
    for (unsigned int i = 0; i < len_book; ++i) {
        if (num_ingr == CookBook[i].num_ingr){
            bool flag = true;
            for (int j = 0; j < num_ingr; ++j) {
                if (ingredients[j] != CookBook[i].ingredients[j]) flag = false;
            }
            if (flag) return CookBook[i];
        }
    }
    Recipe answer = {"__null__", num_ingr, ingredients, 0};
    return answer;
}

int cost_of_dish(string name, Recipe* CookBook, unsigned int len_book){
    return find_recipe(name, CookBook, len_book).cost;
}

int cost_of_dish(int num_ingr, string* ingredients, Recipe* CookBook, unsigned int len_book){
    return find_recipe(num_ingr, ingredients, CookBook, len_book).cost;
}

int num_of_dish(unsigned int TotalGold, string name, Recipe* CookBook, unsigned int len_book){
    return TotalGold / cost_of_dish(name, CookBook, len_book);
}

int num_of_dish(unsigned int TotalGold, int num_ingr, string* ingredients, Recipe* CookBook, unsigned int len_book){
    return TotalGold / cost_of_dish(num_ingr, ingredients, CookBook, len_book);
}

int main() {
    Recipe *CookBook = new Recipe[1000];
    string *borsh_ingredients = new string[5] {"Carrot", "Potato", "Onion", "Meat", "Beet"};
    CookBook[0] = {"Borsh", 5, borsh_ingredients, 100};
    for (int i = 1; i < 1000; ++i) {
        auto str = to_string(i);
        string *ingredients = new string[2] {"Ing1_"+ str, "Ing2_"+ str};
        CookBook[i] = {"dish#" + str, 2, ingredients, i};
    }
    cout << "You will spend " << cost_of_dish("Borsh", CookBook, 1000) << " to create Borsh" << endl;
    cout << "You will spend " << cost_of_dish("dish#242", CookBook, 1000) << " to create dish#242" << endl << endl;
    string *ingredients = new string[2] {"Ing1_777", "Ing2_777"};
    cout << "You will spend " << cost_of_dish(2, ingredients, CookBook, 1000) << " to create dish from Ing1_777 and Ing2_777" << endl << endl;
    cout << "If you have 10000, you can make:" << endl;
    cout << num_of_dish(10000, "Borsh", CookBook, 1000) << " Borshes" << endl;
    cout << "or" << endl;
    cout << num_of_dish(10000, 2, ingredients, CookBook, 1000) <<" dishes from Ing1_777 and Ing2_777" << endl;
    return 0;
}
