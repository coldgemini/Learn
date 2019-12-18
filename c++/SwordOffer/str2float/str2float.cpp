#include <iostream>
#include <cmath>

using namespace std;

bool hasOtherChar(char *str) {
    int i = 0;
    char c;
    while (str[i] != '\0') {
        c = str[i];
        if ((c < '0' || c > '9') && (c != '-') && (c != '.'))
            return true;
        i++;
    }
    return false;
}

bool moreThanOneMinus(char *str) {
    int i = 0;
    char c;
    int count = 0;
    while (str[i] != '\0') {
        c = str[i];
        if (c == '-')
            count++;
        if (count > 1)
            return true;

        i++;
    }
    return false;
}

bool minusNotAtFirst(char *str) {
    int i = 0;
    bool hasMinus = false;
    while (str[i] != '\0') {
        if (str[i] == '-') {
            hasMinus = true;
            break;
        }
        i++;
    }
    if (hasMinus && (i != 0))
        return true;

    return false;
}

bool moreThanOneDot(char *str) {
    int i = 0;
    char c;
    int count = 0;
    while (str[i] != '\0') {
        c = str[i];
        if (c == '.')
            count++;
        if (count > 1)
            return true;

        i++;
    }
    return false;
}

bool dotAtFirst(char *str) {
    int i = 0;
    char c;
    bool hasDot = false;
    while (str[i] != '\0') {
        c = str[i];
        if (c == '.') {
            hasDot = true;
            break;
        }

        i++;
    }
    if (hasDot && (i == 0))
        return true;

    return false;
}

bool zeroAtFirst(char *str) {
    if ((str[0] == '0') && (str[1] != '.'))
        return true;

    return false;
}

bool negZeroAtFirst(char *str) {
    if ((str[0] == '-') && (str[1] == '0') && (str[2] != '.'))
        return true;

    return false;
}

int findLength(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int findDot(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '.')
            return i;
        i++;
    }
    return -1;
}

float cvt2float(char *str) {
    // guard clause
    bool otherChar = hasOtherChar(str);
    cout << "has other char: " << otherChar << endl;
    if (otherChar)
        return 0;

    bool b_moreThanOneMinus = moreThanOneMinus(str);
    cout << "has more than one minus: " << b_moreThanOneMinus << endl;
    if (b_moreThanOneMinus)
        return 0;

    bool b_moreThanOneDot = moreThanOneDot(str);
    cout << "has more than one dot: " << b_moreThanOneDot << endl;
    if (b_moreThanOneDot)
        return 0;

    bool b_minusNotAtFirst = minusNotAtFirst(str);
    cout << "minus not at first: " << b_minusNotAtFirst << endl;
    if (b_minusNotAtFirst)
        return 0;

    bool b_dotAtFirst = dotAtFirst(str);
    cout << "dot at first: " << b_dotAtFirst << endl;
    if (b_dotAtFirst)
        return 0;

    bool b_zeroAtFirst = zeroAtFirst(str);
    cout << "zero at first but not followed by dot: " << b_zeroAtFirst << endl;
    if (b_zeroAtFirst)
        return 0;

    bool b_negZeroAtFirst = negZeroAtFirst(str);
    cout << "negative zero at first but not followed by dot: " << b_negZeroAtFirst << endl;
    if (b_negZeroAtFirst)
        return 0;

    // convert number
    bool isNeg = (str[0] == '-');
    cout << "isNeg: " << isNeg << endl;

    // find length
    int len = findLength(str);
    cout << "len: " << len << endl;
    // find dot
    int dot = findDot(str);
    cout << "dot: " << dot << endl;
    if (dot == -1)
        dot = len;

    // add number
    float sum = 0;
    int i = 0;
    if (isNeg)
        i = 1;
    int num;
    int exp = 0;
    while (str[i] != '\0') {
        if (i == dot) {
            i++;
            continue;
        }
        if (i < dot)
            exp = dot - i - 1;
        else
            exp = dot - i;
        num = str[i] - '0';
        sum += num * pow(10, exp);
        cout << "i: " << i << " num: " << num << " sum: " << sum << endl;
        i++;
    }

    if (isNeg)
        sum = -sum;

    return sum;
}

int main() {
//    char str[] = "-0.02432";
//    char str[] = "0.02432";
//    char str[] = "i.02432";
//    char str[] = "23.02432";
//    char str[] = "2-.302432";
//    char str[] = "-203024320";
    char str[] = "-203.";

    float num = cvt2float(str);

    cout << num << endl;

    return 0;
}

// fail reasons
// 1. other char
// 2. more than one -
// 3. - not at first
// 4. more than one .
// 5. . at first
// 6. 0 at first but not followed by dot
// 7. negative 0 at first but not followed by dot
