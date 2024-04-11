#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <algorithm> 
#include <chrono>
#include <iostream>
#include <vector>

template<typename T>
class AvlTree {
private:
    struct Node {
        T key;
        int height;
        Node *left;
        Node *right;

        Node(T k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node *root;

    int getHeight(Node *node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node *node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(Node *node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    Node *rotateRight(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node *rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node *insertUtil(Node *node, T key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insertUtil(node->left, key);
        else if (key > node->key)
            node->right = insertUtil(node->right, key);
        else
            return node;

        updateHeight(node);

        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *removeUtil(Node *node, T key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key)
            node->left = removeUtil(node->left, key);
        else if (key > node->key)
            node->right = removeUtil(node->right, key);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node *temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;

                delete temp;
            } else {
                Node *temp = findMinUtil(node->right);
                node->key = temp->key;
                node->right = removeUtil(node->right, temp->key);
            }
        }

        if (node == nullptr)
            return nullptr;

        updateHeight(node);

        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node *findMinUtil(Node *node) {
        if (node == nullptr)
            return nullptr;
        if (node->left == nullptr)
            return node;
        return findMinUtil(node->left);
    }

    Node *findMaxUtil(Node *node) {
        if (node == nullptr)
            return nullptr;
        if (node->right == nullptr)
            return node;
        return findMaxUtil(node->right);
    }

    int sizeUtil(Node *node) {
        if (node == nullptr)
            return 0;
        return 1 + sizeUtil(node->left) + sizeUtil(node->right);
    }

public:
    AvlTree() : root(nullptr) {}

    void insert(T key) {
        root = insertUtil(root, key);
    }

    void remove(T key) {
        root = removeUtil(root, key);
    }

    T findMin() {
        Node *minNode = findMinUtil(root);
        if (minNode == nullptr)
            throw stdruntime_error("Tree is empty");
        return minNode->key;
    }

    T findMax() {
        Node *maxNode = findMaxUtil(root);
        if (maxNode == nullptr)
            throw stdruntime_error("Tree is empty");
        return maxNode->key;
    }

    bool isEmpty() {
        return root == nullptr;
    }

    int size() {
        return sizeUtil(root);
    }

    void treeMedian(const std::vector<int> *instructions);
};


#endif  // MYAVLTREE_HPP