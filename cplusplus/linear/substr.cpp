#include <iostream>
#include <string>
#include <tuple>

using namespace std;

int CHARLEN = 256;

struct substr_struct {
    bool found;
    int pos;
    string substr;
};

// the position in 2 which has substring of 1
// will return the first occurance of a substring as ordered in 1 if multiple are found
auto substr(const string &str1, const string &str2) {
    int maxRoll = 0;
    int roll = 0;
    int pos = 0;
    string substr;
    string bestSubstr;
    bool found = false;
    for(int i = 0; i < str1.length(); i++) {
        for(int j = 0; j < str2.length(); j++) {
            if(str2[j] == str1[i]) {
                found = true;
                // if match then keep going to see how far we can get
                roll = 1;
                int k = i;
                int m = j;
                while(k < str1.length()) {
                    if(str2[m] == str1[k]) {
                        substr += str2[m];
                        roll++;
                        k++;
                        m++;
                    }
                    else {
                        break;
                    }
                }
            }
            // if the roll we got was the best we saw far
            if (roll > maxRoll) {
                maxRoll = roll;
                bestSubstr = substr;
                pos = j;
            }
            substr = "";
        }
    }

    return substr_struct{found, pos, bestSubstr};
}


int main() {
    substr_struct s1 = substr("waterbottle", "erbottlewat");
    substr_struct s2 = substr("apple", "plea");
    substr_struct s3 = substr("apple", "apple");
    substr_struct s4 = substr("naur", "ruan");
    substr_struct s5 = substr("orange", "puddl");
    substr_struct s6 = substr("waterwatwat", "watewatwaterwat");

    cout << s1.found << " " << s1.pos << " " << s1.substr << endl;
    cout << s2.found << " " << s2.pos << " " << s2.substr << endl;
    cout << s3.found << " " <<  s3.pos << " " << s3.substr << endl;
    cout << s4.found << " " << s4.pos << " " << s4.substr << endl;
    cout << s5.found << " " << s5.pos << " " << s5.substr << endl;
    cout << s6.found << " " << s6.pos << " " << s6.substr << endl;
}


