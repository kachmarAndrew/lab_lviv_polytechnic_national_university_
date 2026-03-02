#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

Node* insertBST(Node* root, int key) {
    if (!root)
        return new Node(key);

    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}

int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

void printTree(Node* root, int space = 0, int indent = 5) {
    if (!root) return;

    space += indent;

    printTree(root->right, space);

    cout << endl;
    for (int i = indent; i < space; i++)
        cout << " ";
    cout << root->key;

    printTree(root->left, space);
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}


struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int value)
        : key(value), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
    if (!node)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

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

void printAVL(AVLNode* root, int space = 0, int indent = 5) {
    if (!root) return;

    space += indent;

    printAVL(root->right, space);

    cout << endl;
    for (int i = indent; i < space; i++)
        cout << " ";
    cout << root->key;

    printAVL(root->left, space);
}

int main() {

    Node* bstRoot = nullptr;
    AVLNode* avlRoot = nullptr;

    int values[] = {1,2,3,4,5,6,7,8,9};

    cout << "INSERTING: 1 2 3 4 5 6 7 8 9\n\n";

    for (int v : values) {
        bstRoot = insertBST(bstRoot, v);
        avlRoot = insertAVL(avlRoot, v);
    }

    cout << "=== NORMAL BST ===\n";
    printTree(bstRoot);
    cout << "\nHeight of BST = " << height(bstRoot) << endl;

    cout << "\n=== AVL TREE ===\n";
    printAVL(avlRoot);
    cout << "\nHeight of AVL = " << getHeight(avlRoot) << endl;

    freeTree(bstRoot);

    return 0;
}