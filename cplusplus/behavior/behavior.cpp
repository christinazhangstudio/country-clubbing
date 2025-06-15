#include <iostream>
#include <vector>

using namespace std;

int main() {
    int array1[] = {0};
    int array2[10] = {0};
    int array3[] = {0, 1, 2, 3, 4};
    char array4[] = {'0', '1', '2', '3', '4'};
    char array5[] = "hello"; // should be null term

    int a1 = array1[6]; // random garbage
    int a2 = array2[18]; // random garbage
    char a3 = array3[10];  // empty
    char a5 = array5[6]; // null terminator -- prints 0
    char a5c = array5[10]; // some weird behavior.. can be 1, 2, etc.? padding?
    
    // char and int arrays are stored slightly differently
    // char: null termin, compiler added padding, debug builds
    // int: not null termin, can just be whatever was in memory previously

    cout << "accessing out of bounds is ok: " << a1 << " and " << a2 << " and (empty):" << a3  << " and (null termin):" << a5 << " and " << a5c <<endl;

    char a3c = array3[2];
    int a4i = array4[1];
    cout << "casting char to int is ok, but not int to char: " << a3c << " (supposed to be " << array3[2] << ")" << " and " << a4i << endl;
}