#include <iostream>
#include <algorithm>
#include <vector>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

struct BinarySearchTree {
  public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertRec(root, value);
    }

    TreeNode* insertRec(TreeNode* root, int value) {
        if (root == nullptr) {
            return new TreeNode(value);
        }

        if (value < root->data) {
            root->left = insertRec(root->left, value);
        }
        else if (value > root->data) {
            root->right = insertRec(root->right, value);
        }

        return root;
    }

    void inorder() {
        inorderRec(root);
    }

    void inorderRec(TreeNode* root) {
        if (root != nullptr) {
            inorderRec(root->left);
            std::cout << root->data << " ";
            inorderRec(root->right);
        }
    }

  private:
    TreeNode* root;

};

struct VectorBST {

    void insert(int value) {
        auto it = std::lower_bound(tree.begin(), tree.end(), value);
        if (it == tree.end() || *it != value) // Avoid duplicates
            tree.insert(it, value);
    }

    void remove(int value) {
        auto it = std::lower_bound(tree.begin(), tree.end(), value);
        if (it != tree.end() && *it == value) {
            tree.erase(it);
        }
    }

    bool search(int value) {
        return std::binary_search(tree.begin(), tree.end(), value);
    }

    int predecessor(int x) {
        auto it = std::lower_bound(tree.begin(), tree.end(), x);
        if (it == tree.begin()) return -1; // No predecessor exists
        return *(--it);
    }

    int successor(int x) {
        auto it = std::upper_bound(tree.begin(), tree.end(), x);
        if (it == tree.end()) return -1; // No successor exists
        return *it;
    }

    void inorder() {
        for (int v : tree) std::cout << v << " ";
        std::cout << "\n";
    }

    void preorder(int index = 0) {
        if (index >= tree.size()) return;
        std::cout << tree[index] << " ";
        preorder(2 * index + 1); // Left child
        preorder(2 * index + 2); // Right child
    }

    void postorder(int index = 0) {
        if (index >= tree.size()) return;
        postorder(2 * index + 1); // Left child
        postorder(2 * index + 2); // Right child
        std::cout << tree[index] << " ";
    }

private:
    std::vector<int> tree;
};

int main() {
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    std::cout << "Inorder traversal: ";
    bst.inorder();
    std::cout << '\n';


    VectorBST vecbst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(15);
    bst.insert(25);

    std::cout << "Inorder: ";
    vecbst.inorder();

    std::cout << "Preorder: ";
    vecbst.preorder();
    std::cout << "\n";

    std::cout << "Postorder: ";
    vecbst.postorder();
    std::cout << "\n";

    std::cout << "Deleting 10...\n";
    vecbst.remove(10);

    std::cout << "Successor of 20 is: " << vecbst.successor(20) << '\n';
    std::cout << "Predecessor of 20 is: " << vecbst.predecessor(20) << '\n';

    std::cout << "Inorder after deletion: ";
    vecbst.inorder();
}
