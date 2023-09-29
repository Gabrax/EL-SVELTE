#include <iostream>

//A binary search tree (BST) is a data structure in C++ that organizes elements in a hierarchical structure where each node has at most two children,
// a left child, and a right child. The key property of a BST is that for each node:
//
//All nodes in its left subtree have keys less than the node's key.
//All nodes in its right subtree have keys greater than the node's key.

//In this code:
//
//TreeNode represents a node in the binary search tree.
//BinarySearchTree is the class that contains the BST operations.
//The insert function is used to insert values into the BST.
//The inorder function is used to perform an inorder traversal of the BST, which prints the elements in sorted order.

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

class BinarySearchTree {
private:
    TreeNode* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    // Function to insert a value into the BST
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Function to perform the insertion recursively
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

    // Function to perform an inorder traversal of the BST
    void inorder() {
        inorderRec(root);
    }

    // Function to perform the inorder traversal recursively
    void inorderRec(TreeNode* root) {
        if (root != nullptr) {
            inorderRec(root->left);
            std::cout << root->data << " ";
            inorderRec(root->right);
        }
    }
};

int main() {
    BinarySearchTree bst;

    // Insert values into the BST
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    // Perform an inorder traversal to print the elements in sorted order
    std::cout << "Inorder traversal: ";
    bst.inorder();
    std::cout << std::endl;

    return 0;
}