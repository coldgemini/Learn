// C++ program for implementation of Heap Sort
#include <iostream>

using namespace std;


// main function to do heap sort
void bubbleSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = 0; i <= n - 2; i++)
        for (int j = n - 2; j >= i; j--) {
            cout << "i: " << i << " j: " << j << endl;
            if (arr[j + 1] > arr[j])
                swap(arr[j], arr[j + 1]);
        }
}


/* A utility function to print array of size n */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Driver program
int main() {
    int arr[] = {12, 11, 13, 1, 3, 100, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "n: " << n << endl;

    bubbleSort(arr, n);

    cout << "Sorted array is \n";
    printArray(arr, n);
    return 0;
}