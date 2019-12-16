//
// Created by xiang on 12/15/19.
//

#include <string.h>
#include <iostream>

using namespace std;

#define NO_OF_TEST 1

struct studentType {
    string studentID;
    string firstName;
    string lastName;
    string subjectName;
    string courseGrade;
    int arrayMarks[4];
    double avgMarks;
};

studentType input() {
    studentType newStudent;
    cout << "\nPlease enter student information:\n";

    cout << "\nFirst Name: ";
    cin >> newStudent.firstName;

    cout << "\nLast Name: ";
    cin >> newStudent.lastName;

    cout << "\nStudent ID: ";
    cin >> newStudent.studentID;

    cout << "\nSubject Name: ";
    cin >> newStudent.subjectName;

    for (int i = 0; i < NO_OF_TEST; i++) {
        cout << "\nTest " << i + 1 << " mark: ";
        cin >> newStudent.arrayMarks[i];
    }

    return newStudent;
}

int main() {
    studentType s;
    s = input();

    cout << "\n========" << endl << "Collected the details of "
         << s.firstName << endl;

    return 0;
}