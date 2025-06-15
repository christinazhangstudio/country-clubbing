#include <iostream>

using namespace std;

int main() {
    int len = 10;
    // post increment and pre increment in a loop is literally the same thing
    for(int j = len - 1; j >= 0; --j) {
        cout << j;
    }

    cout << endl;

    for(int j = len - 1; j >= 0; j--) {
        cout << j;
    }

    cout << endl;

     for(int j = 0; j <= len; j++) {
        cout << j;
    }

    cout << endl;

     for(int j = 0; j <= len; ++j) {
        cout << j;
    }

    int array[] = {5, 1, 4, 2, 3, 9, 0};

    // illegal
    // for(int i = 0; i < array.length(); i++) {
    // }
    for(int a: array) {
        cout << a;
    }
}