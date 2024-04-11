#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <algorithm> 
#include <chrono>
#include <iostream>
#include <vector>
#include <stdexcept>


// Textbook implementation of an AVL Tree + modifications
// Definition of an AVL Tree class
class AVLTree {
private:
    // Internal structure for tree nodes
    struct Node {
        int value;      // Value stored in the node
        Node *l;        // Pointer to the left child
        Node *r;        // Pointer to the right child
        int height;     // Height of the node

        // Constructor for creating a new node with a given value
        Node(const int &value) : value(value), l(nullptr), r(nullptr), height(1) {}
    };

    Node *root;       // Root node of the AVL tree
    int treeSize;     // Number of nodes in the tree

    // Utility function to get the height of a node
    int getHeight(Node *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Computes the height difference between the left and right children of a node
    int getHeightDiff(Node *node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->l) - getHeight(node->r);
    }

    // Updates the height of a node based on the heights of its children
    void updateHeight(Node *node) {
        node->height = std::max(getHeight(node->l), getHeight(node->r)) + 1;
    }

    // Performs a left rotation around a given node and returns the new root
    Node *rotateLeft(Node *node) {
        Node *newRoot = node->r;
        node->r = newRoot->l;
        newRoot->l = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    // Performs a right rotation around a given node and returns the new root
    Node *rotateRight(Node *node) {
        Node *newRoot = node->l;
        node->l = newRoot->r;
        newRoot->r = node;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    // Helper function to insert a new value into the subtree rooted at a given node
    Node *insertHelper(Node *node, const int &value) {
        if (node == nullptr) {
            treeSize++;
            return new Node(value);
        }

        if (value <= node->value) {
            node->l = insertHelper(node->l, value);
        } else {
            node->r = insertHelper(node->r, value);
        }

        updateHeight(node);

        // Balancing the tree
        int balanceFactor = getHeightDiff(node);
        if (balanceFactor > 1) {
            if (getHeightDiff(node->l) < 0) {
                node->l = rotateLeft(node->l);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getHeightDiff(node->r) > 0) {
                node->r = rotateRight(node->r);
            }
            return rotateLeft(node);
        }

        return node;
    }

    // Helper function to remove a value from the subtree rooted at a given node
    Node *removeHelper(Node *node, const int &value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->value) {
            node->l = removeHelper(node->l, value);
        } else if (value > node->value) {
            node->r = removeHelper(node->r, value);
        } else {
            // Node with only one child or no child
            if (node->l == nullptr || node->r == nullptr) {
                Node *temp = (node->l != nullptr) ? node->l : node->r;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
                treeSize--;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node *temp = min(node->r);
                node->value = temp->value;
                node->r = removeHelper(node->r, temp->value);
            }
        }

        if (node == nullptr)
            return nullptr;

        updateHeight(node);

        // Balancing the tree
        int balanceFactor = getHeightDiff(node);
        if (balanceFactor > 1) {
            if (getHeightDiff(node->l) < 0) {
                node->l = rotateLeft(node->l);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (getHeightDiff(node->r) > 0) {
                node->r = rotateRight(node->r);
            }
            return rotateLeft(node);
        }

        return node;
    }

    // Finds the node with the minimum value in the subtree rooted at a given node
    Node *min(Node *node) {
        if (node == nullptr || node->l == nullptr)
            return node;
        return min(node->l);
    }

    // Finds the node with the maximum value in the subtree rooted at a given node
    Node *max(Node *node) {
        if (node == nullptr || node->r == nullptr)
            return node;
        return max(node->r);
    }

public:
    // Constructor initializes an empty AVL tree
    AVLTree() : root(nullptr), treeSize(0) {}

    // Inserts a new value into the AVL tree
    void insert(const int &value) {
        root = insertHelper(root, value);
    }

    // Removes a value from the AVL tree, if it exists
    void remove(const int &value) {
        root = removeHelper(root, value);
    }

    // Finds and returns the minimum value in the AVL tree
    int findMin() {
        Node *minNode = min(root);
        if (minNode == nullptr)
            throw std::runtime_error("Tree is empty");
        return minNode->value;
    }

    // Finds and returns the maximum value in the AVL tree
    int findMax() {
        Node *maxNode = max(root);
        if (maxNode == nullptr)
            throw std::runtime_error("Tree is empty");
        return maxNode->value;
    }

    // Checks if the AVL tree is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Returns the number of nodes in the AVL tree
    int size() {
        return treeSize;
    }

    void treeMedian(const std::vector<int> *instructions);
};


#endif // MYAVLTREE_HPP
