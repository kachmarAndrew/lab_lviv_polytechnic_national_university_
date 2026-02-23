#include <iostream>

using namespace std;

/////////////////////////////////////////////
// ВУЗОЛ ДЕРЕВА
/////////////////////////////////////////////

struct Node {
    char key;
    Node* left;
    Node* right;
};

/////////////////////////////////////////////
// ДОДАВАННЯ У BST
/////////////////////////////////////////////

Node* insert(Node* root, char key) {
    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->key = key;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

/////////////////////////////////////////////
// ПОШУК КЛЮЧА
/////////////////////////////////////////////

bool search(Node* root, char key) {
    if (root == nullptr)
        return false;

    if (root->key == key)
        return true;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

/////////////////////////////////////////////
// INORDER (ВІДСОРТОВАНИЙ ВИВІД)
/////////////////////////////////////////////

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

/////////////////////////////////////////////
// ГРАФІЧНИЙ ВИВІД ДЕРЕВА
/////////////////////////////////////////////

void printTree(Node* root, int space = 0, int indent = 5) {
    if (root == nullptr)
        return;

    space += indent;

    printTree(root->right, space);

    cout << endl;
    for (int i = indent; i < space; i++)
        cout << " ";
    cout << root->key << "\n";

    printTree(root->left, space);
}

/////////////////////////////////////////////
// ЗВІЛЬНЕННЯ ПАМ’ЯТІ
/////////////////////////////////////////////

void freeTree(Node* root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

/////////////////////////////////////////////
// ГОЛОВНА ПРОГРАМА
/////////////////////////////////////////////

int main() {

    Node* root = nullptr;

    // Формуємо дерево
    char keys[] = {'M', 'F', 'T', 'A', 'H', 'S', 'Z', 'D', 'G'};
    int size = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < size; i++) {
        root = insert(root, keys[i]);
    }

    cout << "Inorder traversal (sorted):\n";
    inorder(root);
    cout << "\n\nTree structure:\n";
    printTree(root);

    // Перевірка ключа 'S'
    char target = 'S';
    cout << "\nChecking for key '" << target << "'...\n";

    if (search(root, target))
        cout << "Vertex with key '" << target << "' EXISTS in the tree.\n";
    else
        cout << "Vertex with key '" << target << "' DOES NOT exist in the tree.\n";

    freeTree(root);

    return 0;
}
