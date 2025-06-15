#include <string>
#include <iostream>

using namespace std;

bool isOneAway(const string &str1, const string &str2) {
    if (abs(int(str1.length())) - int(str2.length()) > 1) {
        return false;
    }

    int len1 = str1.length();
    int len2 = str2.length();
    string smaller = len1 < len2 ? str1 : str2;
    string bigger = len1 > len2 ? str1 : str2;

    bool foundMismatch = false;

    int i = 0, j = 0;
    while(i < smaller.length() && j < bigger.length()) {
        if(smaller[i] != bigger[j]) {
            // bigger could have a char here that smaller doesn't
            // in which we case we need to compare the rest
            // that bigger = smaller
            if(foundMismatch == true) { // already found mismatch
                return false;
            }
            foundMismatch = true;
            j++;
            if (smaller.length() == bigger.length()) {
                i++;
            }
        } else {
            // same char here so increment both
            i++;
            j++;
        }
    }

    return true;
}

int main() {
    cout << "takeway and safeway:" << boolalpha << isOneAway("takeway", "safeway") << endl;
    cout << "safway and safeway:" << boolalpha << isOneAway("safway", "safeway") << endl;
    cout << "takeway and takewa:" << boolalpha << isOneAway("takeway", "takewa") << endl;
    cout << "takeway and taewa:" << boolalpha << isOneAway("takeway", "taewa") << endl;
}