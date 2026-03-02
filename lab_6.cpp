#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node23 {
    vector<int> keys;
    vector<Node23*> children;
    Node23* parent = nullptr;

    Node23(int key) { keys.push_back(key); }
};

void insert(Node23*& root, int key) {
    if (!root) { root = new Node23(key); return; }
    Node23* cur = root;
    while (!cur->children.empty()) {
        if (key < cur->keys[0]) cur = cur->children[0];
        else if (cur->keys.size() == 1 || key < cur->keys[1]) cur = cur->children[1];
        else cur = cur->children[2];
    }
    cur->keys.push_back(key);
    sort(cur->keys.begin(), cur->keys.end());
}

void removeDemo(Node23*& root, int key) {
    if (!root) return;
    if (find(root->keys.begin(), root->keys.end(), key) != root->keys.end()) {
        auto it = find(root->keys.begin(), root->keys.end(), key);
        root->keys.erase(it);
        return;
    }
    for (auto child : root->children) removeDemo(child, key);
}

// Вивід дерева
void printTree(Node23* node, int indent = 0) {
    if (!node) return;
    for (int i = 0; i < indent; i++) cout << " ";
    for (int k : node->keys) cout << k << " ";
    cout << endl;
    for (auto child : node->children) printTree(child, indent + 5);
}

// MAIN
int main() {
    Node23* root = nullptr;
    vector<int> values = {4,6,120,8,15,13,19,20,34,29,100};
    for (int v : values) insert(root, v);

    cout << "2-3 tree after insertion:\n";
    printTree(root);

    vector<int> delKeys = {4,6,8,34};
    for (int k : delKeys) removeDemo(root, k);

    cout << "\n2-3 tree after deletion of 4,6,8,34:\n";
    printTree(root);

    return 0;
}