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
// assumes str1 is bigger than str2
auto substr(const string &str1, const string &str2) {
    // find matching characters
    int roll = 0;
    int maxRoll = 0;
    int pos = 0;
    bool found = false;
    string substr;
    string bestSubstr;
    for(int i = 0; i < str1.length(); i++) {
        for(int j = 0; j < str2.length(); j++) {
            if(str1[i] == str2[j]) {
                found = true;
                roll = 1;
                substr += str2[j];
                // keep going...
                int k = i + 1;
                int m = j + 1;
                while(k < str1.length()) {
                    if(str1[k] == str2[m]) {
                        roll++;
                        substr += str2[m];
                        k++;
                        m++;
                    } else {
                        break;
                    }
                }
            }
            if(roll > maxRoll) {
                maxRoll = roll;
                bestSubstr = substr;
                pos = j;
            }
            substr = "";
        }
    }

    return substr_struct{found, pos, bestSubstr};
}

// returns also the index at which the substring was found in 1
tuple<string, int> remove_substr(const string &str1, const string &substr) {
    // the substring is guaranteed to be in str1
    // so just find and remove it from str1
    string newStr;
    for(int i = 0; i < str1.length(); i++) {
        int j = 0;
        if(str1[i] == substr[j]) {
            int k = i;
            int m = j;
            // see if the rest of the substr is here and remove it
            while(m < substr.length() & k < str1.length()) {
                if(str1[k] == substr[m]) {
                    ++k;
                    ++m;
                } else {
                    // the next char does not match the substr
                    // so clearly this is not our match
                    newStr += str1[i];
                    break;
                }
                // this is whole substr
                if(m == substr.length() - 1) {
                    // add whatever is rest in str1 to newStr
                    for(int i = k + 1; i < str1.length(); i++) {
                        newStr += str1[i];
                    }
                    return {newStr, i};
                }
            }
        } else {
            newStr += str1[i];
        }
    }
    return {"", 0};
}

bool isRotation(const string &str1, const string &str2) {
    // is a rotation if the first found substring
    // is followed by the concatenation of the rest of the word
    if(str1.length() != str2.length()) {
        return false;
    }

    substr_struct s = substr(str1, str2);
    
    
    // find what else is left of str1 without the substring
    auto [remaining_str, idx] = remove_substr(str1, s.substr);
    // idx is where our substring was removed
    int pivot = idx + s.substr.length();
    if(pivot >= str1.length()) {
        // wrap around
        // 0 1 2 3 4
        // 3, 4 -> 7 -> (from 5) = 2
        // 2, 3 -> 5 -> (from 5) = 0
        // 4, 2 -> 6 -> (from 5) = 1
        pivot = pivot - str1.length(); 
    }

    // cout << remaining_str << endl;

    if(remaining_str == "") {
        return false;
    }

    // the remaining str should be concatenated after (can wrap around)
    for(int i = 0; i < remaining_str.length(); i++) {
        if(str1[pivot] != remaining_str[i]) {
            return false;
        }
        ++pivot;
        if(pivot >= str1.length()) { 
            pivot == 0;
        }
    }

    // now we just took the substring of str1 in str2... but we need
    // to make sure str2 also is a rotated version of this word.
    int pivot2 = s.pos + s.substr.length();
    if(pivot2 >= str2.length()) {
        pivot2 = pivot2 - str1.length(); 
    }
    for(int i = 0; i < remaining_str.length(); i++) {
        if(str2[pivot2] != remaining_str[i]) {
            return false;
        }
        ++pivot2;
        if(pivot2 >= str2.length()) { 
            pivot2 == 0;
        }
    }


    return true;
}

int main() {
    cout << "waterbottle, erbottlewat: " << boolalpha << isRotation("waterbottle", "erbottlewat") << endl; // len 11
    cout << "waterbottle, bottlewater: " << boolalpha << isRotation("waterbottle", "bottlewater") << endl;
    cout << "waterbottle, lebottwater: " << boolalpha << isRotation("waterbottle", "lebottwater") << endl; // false
    cout << "waterbottle, ewaterbottl: " << boolalpha << isRotation("waterbottle", "ewaterbottl") << endl;
    cout << "foxy, xyfo: " << boolalpha << isRotation("foxy", "xyfo") << endl;
    cout << "naur, ruan: " << boolalpha << isRotation("naur", "ruan") << endl;  // false
}