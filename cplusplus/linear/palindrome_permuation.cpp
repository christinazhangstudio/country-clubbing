#include <string>
#include <bitset>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string removeSpaces(string str) {
    string result;
    for(char c : str) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

bool isPermutationOfPalindrome(string str) {
    // odd is ok    // 3 / 2 = 1, so will check 0 == 2 and 1 == 1 
   
    // is palindrome
    // int h = str.length() / 2;

    // transform(str.begin(), str.end(), str.begin(), ::tolower);

    // for(int i = 0; i <= h; i++) {
    //     if(str[i] != str[str.length() - 1 - i]) {
    //         return false;
    //     }
    // }
    // return true;

    // what makes permutation of palindrome different from just permutation
    // if it is even string, each char must appear in pairs
    // if it is odd, each char except only one must appear in pairs
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    sort(str.begin(), str.end());
    int isOdd = 0;

    // remove spaces, spaces are stupid
    str = removeSpaces(str);

    // cout << str << endl;
    
    // traverse in pairs
    for(int i = 0; i < str.length(); i += 2) {
        if(i+1 >= str.length()) { // non accessible pos
            // odd string, so the last "pair" is allowed to be odd
            break;
        }
        if(str[i] != str[i+1]) { // 0/1, 2/3, 4 is allowed even though 5 doesn't exist...   // len: 5
            // cout << "wah " << str[i] << str[i+1] << endl;
            isOdd++;
        }
    }

    if(str.length() % 2 == 0) {
        if(isOdd == 0) {
            return true;
        }
        return false;
    }
    // if odd, can have at most 1 odd
    if(isOdd == 1) {
        return true;
    }
    return false;
}

int getCharNumber(const char &c) {
    int a = (int) 'a';
    int z = (int) 'z';
    int A = (int) 'A';
    int Z = (int) 'Z';
    int val = (int)c;
    if (a <= val && val <= z) {
        return val - 'a';
    } else if (A <= val && val <= Z) {
        return val - 'A';
    }
    return -1;
}

bool isPermutationOfPalindrome_bitwise(const string &str) {
    const int numChar = 26;
    bitset<numChar> table(0);
    for (const char &c : str) {
        const int cnum = getCharNumber(c);
        if (cnum == -1) {
            continue;
        }
        table.flip(cnum); // a - z
    }
    const int summary = table.to_ullong(); // converts bitset to int
    const bool isPowerOf2 = ((summary) & (summary - 1)) == 0; 
    // a binary representation that is a power of 2 has exactly one bit set to 1
    // 0001 -> & 0000 = 0
    // 0010 -> & 0001 = 0
    // 0100 -> & 0011 = 0
    // 1000 -> & 0111 = 0
    // by proving only 1 bit is flipped, we can say that there is only 1 char that is "odd"
    // after having made "even" (by flipping its corresponding bit) already.
    return isPowerOf2;
}

int main() {
    vector <string>patterns{
        "",
        "a",
        "bab",
        "abba",
        "acaa",
        "ababa",
        "ab",
        "Tact Coa",
        "Rats live on no evil st",
        "Rats live on no evil star"
    };

    cout << "=== naive ===" << endl;

    for(auto& pattern: patterns) {
        cout << pattern << ": " << boolalpha << isPermutationOfPalindrome(pattern) <<endl;
    }

    
    cout << "=== bitwise ===" << endl;

    for(auto &pattern: patterns) {
        cout << pattern << ": " << boolalpha << isPermutationOfPalindrome_bitwise(pattern) <<endl;
    }
}