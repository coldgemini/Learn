#include <iostream>

using namespace std;


int Fib(int n) {
    int pre = 1;
    int cur = 1;
    int tmp = 0;
    for (int i = 2; i <= n; i++) {
        tmp = cur;
        cur = cur + pre;
        pre = tmp;
        cout << cur << " ";
    }
    cout << endl;
    return cur;
}


int main() {
    int n = 8;
    int fib = Fib(n);

    cout << "fib: " << n << " is " << fib << endl;

    return 0;
}