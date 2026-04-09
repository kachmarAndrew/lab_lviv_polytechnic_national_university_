#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> keys;
    vector<Node*> children;

    Node(int key) {
        keys.push_back(key);
    }

    bool isLeaf() {
        return children.empty();
    }
};

class TwoThreeTree {
private:
    Node* root = nullptr;

    // 🔍 Search
    bool search(Node* node, int key) {
        if (!node) return false;

        for (int k : node->keys) {
            if (k == key) return true;
        }

        if (node->isLeaf()) return false;

        if (key < node->keys[0])
            return search(node->children[0], key);
        else if (node->keys.size() == 1 || key < node->keys[1])
            return search(node->children[1], key);
        else
            return search(node->children[2], key);
    }

    // 🔧 Split
    void split(Node*& node, int& upKey, Node*& newChild) {
        int mid = node->keys[1];

        Node* right = new Node(node->keys[2]);

        if (!node->isLeaf()) {
            right->children.push_back(node->children[2]);
            right->children.push_back(node->children[3]);

            node->children.resize(2);
        }

        node->keys.resize(1);

        upKey = mid;
        newChild = right;
    }

    // ➕ Insert helper
    bool insert(Node*& node, int key, int& upKey, Node*& newChild) {
        if (!node) {
            node = new Node(key);
            return false;
        }

        if (node->isLeaf()) {
            node->keys.push_back(key);
            sort(node->keys.begin(), node->keys.end());

            if (node->keys.size() == 3) {
                split(node, upKey, newChild);
                return true;
            }
            return false;
        }

        int i;
        if (key < node->keys[0]) i = 0;
        else if (node->keys.size() == 1 || key < node->keys[1]) i = 1;
        else i = 2;

        int newUpKey;
        Node* newNode = nullptr;

        if (insert(node->children[i], key, newUpKey, newNode)) {
            node->keys.push_back(newUpKey);
            sort(node->keys.begin(), node->keys.end());

            node->children.insert(node->children.begin() + i + 1, newNode);

            if (node->keys.size() == 3) {
                split(node, upKey, newChild);
                return true;
            }
        }
        return false;
    }

    // 🗑️ Delete (спрощений)
    void collect(Node* node, vector<int>& vals) {
        if (!node) return;

        if (node->isLeaf()) {
            for (int k : node->keys) vals.push_back(k);
        } else {
            for (int i = 0; i < node->keys.size(); i++) {
                collect(node->children[i], vals);
                vals.push_back(node->keys[i]);
            }
            collect(node->children.back(), vals);
        }
    }

public:
    void insert(int key) {
        int upKey;
        Node* newChild = nullptr;

        if (insert(root, key, upKey, newChild)) {
            Node* newRoot = new Node(upKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(newChild);
            root = newRoot;
        }
    }

    bool search(int key) {
        return search(root, key);
    }

    void remove(int key) {
        vector<int> vals;
        collect(root, vals);

        vals.erase(std::remove(vals.begin(), vals.end(), key), vals.end());

        root = nullptr;

        for (int v : vals) {
            insert(v);
        }
    }

    void print(Node* node, int level = 0) {
        if (!node) return;

        cout << string(level * 4, ' ');
        for (int k : node->keys) cout << k << " ";
        cout << endl;

        for (auto child : node->children) {
            print(child, level + 1);
        }
    }

    void print() {
        print(root);
    }
};

int main() {
    TwoThreeTree tree;

    vector<int> values = {7, 9, 10, 2, 20, 15, 50, 120, 54, 63, 23};

    cout << "INSERT \n";
    for (int v : values) {
        tree.insert(v);
    }

    tree.print();

    cout << "\n DELETE \n";

    vector<int> toDelete = {20, 120, 23, 10};

    for (int v : toDelete) {
        cout << "\nDelete: " << v << endl;
        tree.remove(v);
        tree.print();
    }

    cout << "\n SEARCH \n";
    cout << "Find 15: " << tree.search(15) << endl;
    cout << "Find 100: " << tree.search(100) << endl;

    return 0;
}