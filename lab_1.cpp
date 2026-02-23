#include <iostream>
#include <list>
#include <string>

using namespace std;

bool isSymmetric(const string& input) {
    list<char> symbols;

    for (char ch : input) {
        symbols.push_back(ch);
    }

    auto middle = symbols.begin();
    int zeroCount = 0;

    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        if (*it == '0') {
            middle = it;
            zeroCount++;
        }
    }

    if (zeroCount != 1) {
        return false;
    }

    auto left = middle;
    auto right = middle;

    if (left == symbols.begin() || ++right == symbols.end()) {
        return false;
    }

    --left;

    while (true) {
        if (*left != *right) {
            return false;
        }

        if (left == symbols.begin() || ++right == symbols.end()) {
            break;
        }

        --left;
    }

    return true;
}

int main() {
    string input;
    cout << "Enter string: ";
    cin >> input;

    if (isSymmetric(input)) {
        cout << "The string is symmetric relative to 0." << endl;
    } else {
        cout << "The string is NOT symmetric relative to 0." << endl;
    }

    return 0;
}
