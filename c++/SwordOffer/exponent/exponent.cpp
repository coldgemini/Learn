#include <iostream>
#include <cstdlib>

using namespace std;

int sign(int x) {
    return (x >= 0) ? 1 : 0;
}

double pos_exponent(double base, int exp) {
    double res = 1;
    for (int i = 0; i < exp; i++) {
        res = res * base;
    }
    return res;
};

double exponent(double base, int exp) {
    int exp_sign = sign(exp);
    int exp_pos = abs(exp);

    double res_pos = pos_exponent(base, exp_pos);

    double res;
    if (exp_sign > 0)
        res = res_pos;
    else
        res = 1.0 / res_pos;
    return res;
}

int main() {
    double base = 2.0;
    int exp = -4;

    double res = exponent(base, exp);

    cout << "base: " << base << " exp: " << exp << " result: " << res << endl;

    return 0;
}