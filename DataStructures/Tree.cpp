#include <iostream>

//In C++, you can implement a tree data structure using various approaches, including linked lists, arrays, and classes.
//One of the most common types of trees is the binary tree, where each node has at most two children: a left child and a right child.

//In this example, we define a TreeNode class to represent individual nodes of the binary tree and a BinaryTree class to manage the tree.
// The insert function allows you to insert values into the tree,
// and the inorderTraversal function performs an in-order traversal of the tree to print its elements in sorted order.

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() {
        root = nullptr;
    }

    // Insert a value into the binary tree
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Helper function to insert a value recursively
    TreeNode* insertRec(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }

        return node;
    }

    // Inorder traversal of the binary tree
    void inorderTraversal(TreeNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    // Public function to perform inorder traversal
    void inorder() {
        inorderTraversal(root);
    }
};

int main() {
    BinaryTree tree;

    // Insert values into the binary tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Perform inorder traversal to print the tree elements in sorted order
    std::cout << "Inorder Traversal: ";
    tree.inorder();
    std::cout << std::endl;

    return 0;
}
