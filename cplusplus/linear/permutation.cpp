#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

bool isPermutation(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    for(int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }

    return true;
}

bool isPermutation_count(string str1, string str2) {
    if(str1.size() != str2.size()) {
        return false;
    }

    int count[256] = {0};
    for(int i = 0; i < str1.length(); i++) {
        int val = str1[i];
        count[val]++;
    }
    for(int i = 0; i < str2.length(); i++) {
        int val = str2[i];
        count[val]--;
    }

    // pretends we didn't just user 256
    int n = sizeof(count) / sizeof(count[0]);
    for(int i = 0; i < n; i++) {
        if(count[i] != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << "=== sort ===" <<endl;
    string word1 = "panda";
    string word2 = "danda";
    cout << word1 << " and " << word2 << ": " << boolalpha << isPermutation(word1, word2) << endl;

    string word3 = "panda";
    string word4 = "pandy";
    cout << word3 << " and " << word4 << ": " << boolalpha << isPermutation(word3, word4) << endl;

    string word5 = "gorillas";
    string word6 = "aglilors";
    cout << word5 << " and " << word6 << ": " << boolalpha << isPermutation(word5, word6) << endl;

    cout << "=== count by char occurrances ===" <<endl;

    cout << word1 << " and " << word2 << ": " << boolalpha << isPermutation_count(word1, word2) << endl;

    cout << word3 << " and " << word4 << ": " << boolalpha << isPermutation_count(word3, word4) << endl;

    cout << word5 << " and " << word6 << ": " << boolalpha << isPermutation_count(word5, word6) << endl;
}