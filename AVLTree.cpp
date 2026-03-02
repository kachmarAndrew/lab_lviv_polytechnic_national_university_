#include <iostream>
#include <algorithm>

using namespace std;

/////////////////////////////////////////////////////
// ВУЗОЛ AVL
/////////////////////////////////////////////////////

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value)
        : key(value), left(nullptr), right(nullptr), height(1) {}
};

/////////////////////////////////////////////////////
// AVL TREE
/////////////////////////////////////////////////////

class AVLTree {
private:
    Node* root;

    ////////////////////////////////////////////
    // Висота вузла
    ////////////////////////////////////////////
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    ////////////////////////////////////////////
    // Баланс-фактор
    ////////////////////////////////////////////
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    ////////////////////////////////////////////
    // Правий поворот (Right Rotation)
    ////////////////////////////////////////////
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    ////////////////////////////////////////////
    // Лівий поворот (Left Rotation)
    ////////////////////////////////////////////
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    ////////////////////////////////////////////
    // Вставка з балансуванням
    ////////////////////////////////////////////
    Node* insert(Node* node, int key) {
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // дублікати не вставляємо

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // LL
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // RR
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // LR
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    ////////////////////////////////////////////
    // Підрахунок вершин глибини n
    ////////////////////////////////////////////
    int countDepth(Node* node, int target, int current) {
        if (!node) return 0;

        if (current == target)
            return 1;

        return countDepth(node->left, target, current + 1) +
               countDepth(node->right, target, current + 1);
    }

    ////////////////////////////////////////////
    // Гарний вивід
    ////////////////////////////////////////////
    void printTree(Node* node, int space) {
        if (!node) return;

        space += 5;

        printTree(node->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << node->key;

        printTree(node->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int countNodesAtDepth(int depth) {
        return countDepth(root, depth, 0);
    }

    void print() {
        printTree(root, 0);
        cout << endl;
    }
};

/////////////////////////////////////////////////////
// MAIN
/////////////////////////////////////////////////////

int main() {

    AVLTree tree;

    // вставляємо спеціально в "поганому" порядку
    int values[] = {1,2,3,4,5,6,7,8,9};

    for (int v : values)
        tree.insert(v);

    cout << "AVL Tree structure:\n";
    tree.print();

    int depth = 2;
    cout << "\nNodes at depth " << depth << " = "
         << tree.countNodesAtDepth(depth) << endl;

    return 0;
}