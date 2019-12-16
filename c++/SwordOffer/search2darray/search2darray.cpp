#include <iostream>
#include <vector>

void print_vector2d(std::vector<std::vector<int>> vec2d) {
    std::cout << "vector 2d:" << std::endl;
    for (const auto &vec1d : vec2d) {
        for (const auto &i : vec1d)
            std::cout << i << ' ';
        std::cout << std::endl;
    }
}

struct queryResult {
    bool isInArray;
    int i;
    int j;
};

queryResult
isInArray0(const std::vector<std::vector<int>> &arr, const int &row_min, const int &row_max, const int &col_min,
           const int &col_max, int &i, int &j, const int &query) {
    if (row_min > row_max) {
        queryResult res = {false, 0, 0};
        return res;
    }
    if (col_min > col_max) {
        queryResult res = {false, 0, 0};
        return res;
    }
    int num = arr[row_min][col_max];
    if (query == num) {
        i = row_min;
        j = col_max;
        queryResult res = {true, i, j};
        return res;
    } else if (query > num)
        return isInArray0(arr, row_min + 1, row_max, col_min, col_max, i, j, query);
    else
        return isInArray0(arr, row_min, row_max, col_min, col_max - 1, i, j, query);
}

bool isInArray1(const std::vector<std::vector<int>> &arr, const int &row_min, const int &row_max, const int &col_min,
                const int &col_max, int &i, int &j, const int &query) {
    if (row_min > row_max)
        return false;
    if (col_min > col_max)
        return false;
    int num = arr[row_min][col_max];
    if (query == num) {
        i = row_min;
        j = col_max;
        return true;
    } else if (query > num)
        return isInArray1(arr, row_min + 1, row_max, col_min, col_max, i, j, query);
    else
        return isInArray1(arr, row_min, row_max, col_min, col_max - 1, i, j, query);
}

bool isInArray2(const std::vector<std::vector<int>> &arr, const int &rows, const int &cols, int &i, int &j,
                const int &query) {
    i = 0;
    j = cols - 1;
    int num = 0;
    while (i < rows and j > 0) {
        num = arr[i][j];
        if (query == num)
            return true;
        else if (query > num)
            i++;
        else
            j--;
    }
    return false;
}

int main() {
    const int rows = 2;
    const int cols = 3;
    std::vector<std::vector<int>> arr2d{{1, 2, 3},
                                        {2, 4, 5},
                                        {4, 6, 9}};

    std::cout << "size: " << arr2d.size() << std::endl;
    std::cout << "size: " << arr2d[0].size() << std::endl;
    print_vector2d(arr2d);

    bool res = false;
    queryResult qRes;
    int query = 5;

    int i = 0;
    int j = 0;

    qRes = isInArray0(arr2d, 0, rows - 1, 0, cols - 1, i, j, query);
    res = qRes.isInArray;
    i = qRes.i;
    j = qRes.j;
//    res = isInArray1(arr2d, 2, 3, i, j, query);
//    res = isInArray2(arr2d, 2, 3, i, j, query);

    std::cout << "query " << query << " isInArray: " << res << ", i: " << i + 1 << " j: " << j + 1 << std::endl;
    return 0;
}