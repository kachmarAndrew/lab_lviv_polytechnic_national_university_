#include <iostream>
#include <string>
using namespace std;

class FamilyBST {
private:

    struct Person {
        string name;
        int age;
    };

    struct Node {
        Person person;
        Node* left;
        Node* right;
    };

    Node* root;

    Node* insert(Node* node, Person p) {
        if (node == nullptr) {
            Node* newNode = new Node{p, nullptr, nullptr};
            return newNode;
        }

        if (p.age < node->person.age)
            node->left = insert(node->left, p);
        else if (p.age > node->person.age)
            node->right = insert(node->right, p);

        return node;
    }

    bool search(Node* node, int age) {
        if (node == nullptr)
            return false;

        if (node->person.age == age)
            return true;

        if (age < node->person.age)
            return search(node->left, age);
        else
            return search(node->right, age);
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->person.name << " (" << node->person.age << ")\n";
            inorder(node->right);
        }
    }

    void printTree(Node* node, int space, int indent = 5) {
        if (node == nullptr)
            return;

        space += indent;

        printTree(node->right, space);

        cout << endl;
        for (int i = indent; i < space; i++)
            cout << " ";
        cout << node->person.name << "(" << node->person.age << ")\n";

        printTree(node->left, space);
    }

    void freeTree(Node* node) {
        if (node != nullptr) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

public:

    FamilyBST() {
        root = nullptr;
    }

    ~FamilyBST() {
        freeTree(root);
    }

    void add(string name, int age) {
        root = insert(root, {name, age});
    }

    bool exists(int age) {
        return search(root, age);
    }

    void printSorted() {
        inorder(root);
    }

    void showTree() {
        printTree(root, 0);
    }
};

int main() {

    FamilyBST family;


    family.add("Brother", 18);
    family.add("Grandfather", 75);
    family.add("Me", 20);
    family.add("Sister", 15);
    family.add("Mother", 48);
    family.add("Father", 50);

    cout << "Sorted family (by age):\n";
    family.printSorted();

    cout << "\nTree structure:\n";
    family.showTree();

    int targetAge = 50;
    cout << "\nSearching for age " << targetAge << "...\n";

    if (family.exists(targetAge))
        cout << "Person with this age EXISTS\n";
    else
        cout << "Person NOT found\n";

    return 0;
}