#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool hasDuplicates(const vector<int>& arr) {
    unordered_set<int> seen;

    for (int num : arr) {
        if (seen.count(num)) {
            return true; // дубль знайдено
        }
        seen.insert(num);
    }

    return false;
}

int main() {
    vector<int> arr = {1, 5, 3, 7, 9, 5};

    if (hasDuplicates(arr)) {
        cout << "Duplicates found!" << endl;
    } else {
        cout << "No duplicates." << endl;
    }

    return 0;
}