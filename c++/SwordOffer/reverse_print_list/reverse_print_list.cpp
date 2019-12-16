#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

void print_vec(std::vector<int> vec) {
    std::cout << "vector 1d:" << std::endl;
    for (const auto &i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;
}

void print_reverse_list(list<int> list) {
    vector<int> vec;
    for (const auto i:list) {
        vec.push_back(i);
    }
    reverse(vec.begin(), vec.end());
    print_vec(vec);
}

int main() {
    int n[] = {1, 2, 3, 4, 5};
    std::list<int> list(n, n + 5);

    print_reverse_list(list);

    return 0;
}