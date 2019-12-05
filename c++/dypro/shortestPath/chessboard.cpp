#include <iostream>

using namespace std;


/* A utility function to print array of size n */
void printMatrix(int arr[4][4], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int findPath(int arr[4][4], int n, int m) {
    cout << "find path: " << endl;
    int path[4][4];
    int upper = 0;
    int left = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (i == 0)
                upper = 100;
            else
                upper = path[i - 1][j];

            if (j == 0)
                left = 100;
            else
                left = path[i][j - 1];
            if (i == 0 && j==0){
                upper = 0;
                left = 0;
            }

            path[i][j] = arr[i][j] + min(upper, left);
        }
    printMatrix(path, n, m);
    return path[4 - 1][4 - 1];
}

// Driver program
int main() {
    int arr[4][4] = {
            {1, 1, 1, 0},
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {0, 0, 0, 2}
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = sizeof(arr[0]) / sizeof(arr[0][0]);
    cout << "n: " << n << " m: " << m << endl;
    printMatrix(arr, n, m);

    int length = findPath(arr, n, m);

    cout << "shortestPath is: " << length << endl;
    return 0;
}