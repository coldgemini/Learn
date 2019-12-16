//
#include <iostream>
#include <list>

using namespace std;

void print_list0(std::list<int> list) {
    for (const auto &i : list) {
        cout << i << ", ";
    }
    std::cout << std::endl;
}

void print_list1(std::list<int> list) {
    for (auto i = list.begin(); i != list.end(); i++) {
        cout << *i << ", ";
    }
    std::cout << std::endl;
}

int main() {
    int n[] = {1, 2, 3, 4, 5};
    std::list<int> list(n, n + 5);
//    list1.push_back(0);
//    list1.push_back(1);

    cout << "size: " << list.size() << endl;
    cout << "max size: " << list.max_size() << endl;
    cout << "empty: " << list.empty() << endl;
    print_list0(list);
    print_list1(list);

    return 0;
}
