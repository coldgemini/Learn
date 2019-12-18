#include <iostream>

using namespace std;


void findMinRecur(int *arr, const int pivot, int &min, int begin, int end) {
    int mid = (begin + end) / 2;
    cout << mid << ' ' << min << endl;
    int mval = arr[mid];

    if (mval < min)
        min = mval;

    if (begin >= end)
        return;

    if (mval > pivot) {
        begin = mid + 1;
        findMinRecur(arr, pivot, min, begin, end);
    } else {
        end = mid - 1;
        findMinRecur(arr, pivot, min, begin, end);
    }

}

int findMin(int *arr, int len) {
    int begin = 0;
    int end = len - 1;
    int min = arr[0];
    findMinRecur(arr, min, min, begin, end);
    return min;
}


int main() {
    int arr[] = {5, 6, 7, 8, 9, 1, 2, 3, 4};
    int len = sizeof(arr) / sizeof(arr[0]);

    int min = findMin(arr, len);

    std::cout << "min: " << min << std::endl;


    return 0;
}