// AvlTree.hpp
#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

#include <algorithm>
#include <stdexcept>
#include <iostream>

template<typename Comparable>
class AvlTree {
public:
    AvlTree() : root(nullptr) {}

    AvlTree(const AvlTree & rhs) : root(nullptr) {
        root = clone(rhs.root);
    }

    ~AvlTree() {
        makeEmpty();
    }

    void insert(const Comparable & x) {
        insert(x, root);
    }

    void remove(const Comparable & x) {
        remove(x, root);
    }

    const Comparable & findMin() const {
        if (isEmpty())
            throw std::runtime_error("Attempted to find min in an empty tree.");
        return findMin(root)->element;
    }

    const Comparable & findMax() const {
        if (isEmpty())
            throw std::runtime_error("Attempted to find max in an empty tree.");
        return findMax(root)->element;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    // Placeholder for getMedian implementation
    Comparable getMedian() const {
        if (isEmpty())
            throw std::runtime_error("Attempted to get median from an empty tree.");
        // Implementation depends on your median tracking strategy
        // This could be a direct calculation or maintained during insertion/removal
        return Comparable{}; // Placeholder return
    }

private:
    struct AvlNode {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;
        int count; // To handle duplicates

        AvlNode(const Comparable & elem, AvlNode *lt, AvlNode *rt, int h = 0, int c = 1)
            : element(elem), left(lt), right(rt), height(h), count(c) {}
    };

    AvlNode *root;

    void insert(const Comparable & x, AvlNode * & t) {
        if (t == nullptr)
            t = new AvlNode(x, nullptr, nullptr);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            t->count++; // Duplicate; increment count.
        balance(t);
    }

    void remove(const Comparable & x, AvlNode * & t) {
        if (t == nullptr)
            return; // Item not found; do nothing.
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) { // Two children
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    // Balance, rotations, and other utility methods
    // Implementations go here, following the same pattern as insert and remove

    // Utility method implementations (e.g., makeEmpty, findMin, findMax, balance, rotations)
};

// Due to template definition requirements, implementations should remain in the header.

#endif // MYAVLTREE_HPP
