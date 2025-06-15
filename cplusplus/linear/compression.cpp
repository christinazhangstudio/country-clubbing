#include <iostream>
#include <string>

using namespace std;

string compress(const string &str) {
    string compressed{""};

    // count subsequent occurrances of char and append onto compressed
    for(int i = 0; i < str.length() - 1; i++) {
        char c = str[i];
        
        int count = 1;
        // increment i until we find something not this char
        while(c == str[i+1]) {
            count++;
            i++;
        }

        compressed += c + to_string(count);
    }

    return compressed;
}

int main() {
    cout << "aabcccccaaa compressed: " << compress("aabcccccaaa") << endl;
    cout << "abca compressed: " << compress("abca") << endl;
}
