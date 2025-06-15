#include <iostream>
#include <cstring>

using namespace std;

// strlen is O(n) so there's one downside of using C-style pointers
// to convert, need c_str
// it is like const& string str in that no copy is made and is pass by reference
// however const prevents the func from modifying the string -- good for avoiding copy overhead AND have immodifiability
// string str is just a local copy.
// use string& str for non-const reference.
void urlify(char *str, int len) {
    int numOfSpaces = 0;
    int i = 0, j = 0;
    // preincrement is technically idiomatic because avoids overhead of temp copy
    // but functionally same to postincrement when used in a for loop like this
    for(i = 0; i < len; ++i) {
        if(str[i] == ' ') {
            ++numOfSpaces;
        }
    }

    // need 2 more char positions to put in %20 instead of ' '
    int extendedLen = len + 2 * numOfSpaces;
    i = extendedLen - 1; // i tracks the index in our new string
    for(j = len - 1; j >= 0; --j) {
        if(str[j] != ' ') {
            str[i--] = str[j];
        } else {
            // plug in the values backwards
            str[i--] = '0';
            str[i--] = '2';
            str[i--] = '%';
        }
    }

}

int main() {
    char str[] = "Mr John Smith   ";
    urlify(str, 13);
    cout << str;
}