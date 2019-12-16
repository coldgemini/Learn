#include <iostream>
#include <cstring>

using namespace std;

void replaceSpace(char *str, int length) {
    // find oldlen, newlen
    int oldlen = 0;
    int newlen = 0;
    while (str[oldlen] != '\0') {
        if (str[oldlen] == ' ') {
            newlen += 2;
        }
        oldlen++;
        newlen++;
    }
    cout << "oldlen: " << oldlen << ", newlen: " << newlen << endl;

    // if newlen > length, throw exception
    if (newlen > length) {
        cerr << "length not enough!" << endl;
        return;
    }

    // replace
    int old_idx = oldlen - 1;
    int new_idx = newlen - 1;
    while (old_idx >= 0) {
        if (str[old_idx] != ' ') {
            str[new_idx--] = str[old_idx--];
        } else {
            str[new_idx--] = '0';
            str[new_idx--] = '2';
            str[new_idx--] = '%';
            old_idx--;
        }
    }
}

int main() {
    char str[] = "Hello world";
    int len = strlen(str);
    char *str_total;
    const int length = 20;
    str_total = new char[length];
    for (int i = 0; i < length; i++)
        str_total[i] = ' ';
    int len_total = strlen(str_total);
    std::cout << "total length: " << len_total << std::endl;
    strcpy(str_total, str);
    len_total = strlen(str_total);
    std::cout << "total length: " << len_total << std::endl;

    std::cout << "length: " << len << std::endl;
    std::cout << "old str: " << str_total << std::endl;

    replaceSpace(str_total, length);

    std::cout << "new str: " << str_total << std::endl;

    return 0;
}