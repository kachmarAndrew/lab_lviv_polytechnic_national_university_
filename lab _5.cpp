#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

class BalancedBinaryTree {
private:
    Node* root;

    Node* build(const vector<int>& arr, int left, int right) {
        if (left > right)
            return nullptr;

        int mid = left + (right - left) / 2;

        Node* node = new Node(arr[mid]);

        node->left = build(arr, left, mid - 1);
        node->right = build(arr, mid + 1, right);

        return node;
    }

    int countNodesAtDepth(Node* node, int targetDepth, int currentDepth) const {
        if (!node)
            return 0;

        if (currentDepth == targetDepth)
            return 1;

        return countNodesAtDepth(node->left, targetDepth, currentDepth + 1) +
               countNodesAtDepth(node->right, targetDepth, currentDepth + 1);
    }

    void inorderTraversal(Node* node) const {
        if (!node)
            return;

        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }

public:

    BalancedBinaryTree(const vector<int>& sortedArray) {
        root = build(sortedArray, 0, sortedArray.size() - 1);
    }

    int countDepth(int depth) const {
        return countNodesAtDepth(root, depth, 0);
    }

    void printInorder() const {
        inorderTraversal(root);
        cout << endl;
    }

};

/////////////////////////////////////////////////////
// MAIN
/////////////////////////////////////////////////////

int main() {

    // Дані одразу в коді (без введення)
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    BalancedBinaryTree tree(data);

    cout << "Inorder traversal:\n";
    tree.printInorder();

    int depth = 2;
    cout << "Number of nodes at depth " << depth << " = "
         << tree.countDepth(depth) << endl;


    return 0;
}