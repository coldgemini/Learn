#include <iostream>
#include <list>

using namespace std;

void printList(const list<int> &list) {
    for (int i:list)
        cout << i << " ";
    cout << endl;
}

void printList1(list<int> &list) {
    for (auto i = list.begin(); i != list.end(); i++) {
        cout << *i << ", ";
    }
    std::cout << std::endl;
}


int find_last_kth(const list<int> &list, int k) {
    auto fast = list.begin();
    auto slow = list.begin();
    int fast_pos = 0;

    while (fast != list.end()) {
        cout << "fpos: " << fast_pos << " fast: " << *fast << " slow: " << *slow << endl;
        fast++;
        fast_pos++;

        if (fast_pos >= k + 1)
            slow++;
    }
    cout << "fpos: " << fast_pos << " fast: " << *fast << " slow: " << *slow << endl;
    return *slow;
}

int main() {
    list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 0, 7};

    printList(list);
//    printList1(list);

    int k = 3;
    int val;
    val = find_last_kth(list, k);

    cout << "val: " << val << endl;

    return 0;
}