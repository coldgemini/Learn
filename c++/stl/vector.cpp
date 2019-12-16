#include <iostream>
#include <vector>

void print_vector0(std::vector<int> vec) {
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << ' ';
    std::cout << std::endl;
}

void print_vector1(std::vector<int> vec) {
    for (const auto &i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;
}

void print_vector2(std::vector<int> vec) {
    for (auto i = vec.begin(); i != vec.end(); i++)
        std::cout << *i << ' ';
    std::cout << std::endl;
}

void print_vector3(std::vector<int> vec) {
    for (std::vector<int>::const_iterator i = vec.begin(); i != vec.end(); i++)
        std::cout << *i << ' ';
    std::cout << std::endl;
}

int main() {
    std::vector<std::vector<int>> arr2d{{1, 1, 1},
                                        {2, 2, 2}};
    std::vector<int> vec1;
    vec1.push_back(0);
    vec1.push_back(1);

    print_vector0(vec1);
    print_vector1(vec1);
    print_vector2(vec1);
    print_vector3(vec1);

    return 0;
}
