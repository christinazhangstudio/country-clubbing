#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

bool isUniqueChars(const string &str){
    if (str.length() > 128) {
        return false;
    }
    vector<bool> char_set(128);
    for (int i = 0; i < str.length(); i++){
        int val = str[i];   
        if(char_set[val]) {
            return false;
        }
        // cout << sizeof(string) <<endl;     // string is 32 bytes (a pointer to the character data is 8 bytes, the size field to store the length is 8 bytes, and total size is 24-32 on 64b systems depending on implementation libc++ or libstdc++)
        // cout << sizeof(val) <<endl;        // int (val) is 4 bytes
        // cout << sizeof(char) <<endl;       // char is 1 byte (8 bits)
        // cout << sizeof(bool) <<endl;       // bool is 1 byte (8 bits)
        char_set[val]=true;
    }
    return true;
}

bool isUniqueChars_bitvector(const string &str){
    // space usage is reduced by 8x using bitvector
    // instead of storing int (1 byte)
    // now just using 1 bit
    bitset<256> bits(0);
    for(int i = 0; i < str.length(); i++) {
        int val = str[i];
        if(bits.test(val) > 0) {
            return false;
        }
        bits.set(val);
    }
    return true;
}

bool isUniqueChars_noDS(string str) {
    sort(str.begin(), str.end());   // O(nlogn)

    for (int i = 0; i < str.size() - 1; i++) {
        if(str[i] == str[i+1]) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<string> words = {"derail", "handsome", "shoes", "turtle"};
    cout << "=== naive ===" <<endl;
    for (auto word: words){
        cout << word << string(": ") << boolalpha << isUniqueChars(word) <<endl;
    }

    cout << "=== bitset ==="<<endl;
    for(auto word: words) {
        cout << word << string(": ") << boolalpha << isUniqueChars_bitvector(word) <<endl;
    }

    cout << "=== no data structures ==="<<endl;
    for(auto word: words) {
        cout << word << string(": ") << boolalpha << isUniqueChars_noDS(word) <<endl;
    }
}