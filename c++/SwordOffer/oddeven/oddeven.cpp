#include <iostream>

using namespace std;

void printArray(int arr[], int len) {
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void oddeven0(int arr[], int len) {
    int tmp = 0;
    int odd = 0;
    int even = len - 1;
    while (odd < even) {
        // find non-odd
        while (arr[odd] % 2 != 0)
            odd++;

        // find non-even
        while (arr[even] % 2 == 0)
            even--;

        // swap
        tmp = arr[odd];
        arr[odd] = arr[even];
        arr[even] = tmp;

        // increment
        odd++;
        even--;
    }
}

void oddeven1(int arr[], int len) {
    int tmp = 0;
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (arr[j] % 2 == 0 && arr[j + 1] % 2 != 0) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, len);

    oddeven1(arr, len);

    printArray(arr, len);

    return 0;
}