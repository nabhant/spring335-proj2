#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <algorithm> 
#include <chrono>
#include <iostream>
#include <vector>

template <typename T>
class AvlTree {
private:
    struct AvlNode {
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const T& ele, AvlNode *lt = nullptr, AvlNode *rt = nullptr, int h = 0)
            : element(ele), left(lt), right(rt), height(h) {}
    };

    AvlNode *root;

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        makeEmpty(root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    const T& findMin() const {
        return findMin(root)->element;
    }

    const T& findMax() const {
        return findMax(root)->element;
    }

    void insert(const T& x) {
        insert(x, root);
    }

    void remove(const T& x) {
        remove(x, root);
    }

    int size() const {
        return getSize(root);
    }

    void treeMedian(const std::vector<int> *instructions);

private:
    void insert(const T& x, AvlNode*& t) {
        if (t == nullptr)
            t = new AvlNode(x, nullptr, nullptr);
        else if (x < t->element) {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
                if (x < t->left->element)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
        } else if (t->element < x) {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
                if (t->right->element < x)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
        }


        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    void remove(const T& x, AvlNode*& t) {
        if (t == nullptr) return;

        if (x < t->element) {
            remove(x, t->left);
        } else if (t->element < x) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) { 
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            AvlNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    void balance(AvlNode*& t) {
        if (t == nullptr) return;

        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }

        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    static const int ALLOWED_IMBALANCE = 1;

    void rotateWithLeftChild(AvlNode*& k2) {
        AvlNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = std::max(height(k2->left), height(k2->right)) + 1;
        k1->height = std::max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AvlNode*& k1) {
        AvlNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = std::max(height(k1->left), height(k1->right)) + 1;
        k2->height = std::max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AvlNode*& k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AvlNode*& k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    int height(AvlNode* t) const {
        return t == nullptr ? -1 : t->height;
    }

    void makeEmpty(AvlNode*& t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    AvlNode* findMin(AvlNode* t) const {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    AvlNode* findMax(AvlNode* t) const {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    int getSize(AvlNode* t) const {
        if (t == nullptr) return 0;
        return 1 + getSize(t->left) + getSize(t->right);
    }
};

#endif // MYAVLTREE_HPP
