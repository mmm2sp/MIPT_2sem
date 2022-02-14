#include <iostream>

using namespace std;

/*
 * Проверка правильности скобочностной последовательности (заканчивается @)
 */

bool sequence_is_correct(char last_bracket) {
    bool answer = true;
    char c;
    do {
        cin >> c;
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            answer = sequence_is_correct(c);
        }
        else {
            if (last_bracket == '(') {
                if (c == ')') return true;
                if (c == ']' || c == '}' || c == '>') return false;
            }
            if (last_bracket == '[') {
                if (c == ']') return true;
                if (c == ')' || c == '}' || c == '>') return false;
            }
            if (last_bracket == '{') {
                if (c == '}') return true;
                if (c == ')' || c == ']' || c == '>') return false;
            }
            if (last_bracket == '<') {
                if (c == '>') return true;
                if (c == ')' || c == ']' || c == '}') return false;
            }
        }
    } while(c != '@' && answer == true);
    if (c == '@' && last_bracket != ' ') answer = false; // {() isn't correct sequence
    return answer;
}

bool check_seq(){
    /*
     * Returns true if sequence is OK and false in another way
     */
    return sequence_is_correct(' ');
}

int main(int argc, char **argv) {
    bool answer = check_seq();
    cout << answer << endl;
    return 0;
}
