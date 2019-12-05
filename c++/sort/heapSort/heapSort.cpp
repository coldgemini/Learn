// C++ program for implementation of Heap Sort
#include <iostream>

using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapify2(int arr[], int lastIdx, int root) {
    int largest = root; // largest initialized to root
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    // find largest
    if (left <= lastIdx && arr[left] > arr[largest])
        largest = left;
    if (right <= lastIdx && arr[right] > arr[largest])
        largest = right;
    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, lastIdx, largest);
    }

}

// main function to do heap sort
void heapSort(int arr[], int n) {
    cout << "heapSort" << endl;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void heapSort2(int arr[], int size) {
    cout << "heapSort2" << endl;
    // build heap
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify2(arr, size - 1, i);
    }
    // swap max element one by one
    for (int i = size - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify2(arr, i - 1, 0);
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
    int arr[] = {12, 11, 13, 1, 3,100, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

//    heapSort(arr, n);
    heapSort2(arr, n);

    cout << "Sorted array is \n";
    printArray(arr, n);
}