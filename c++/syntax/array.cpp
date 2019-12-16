#include <iostream>

using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4};
    cout << arr[0] << endl;

    int *arr1 = arr + 1;
    cout << arr1[0] << endl;

    return 0;
}