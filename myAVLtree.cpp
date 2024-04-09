#include "myAVLTree.hpp"
#include <vector>
#include <iostream>

void treeMedian(const std::vector<int>* instructions) {
    AvlTree<int> tree;
    std::vector<int> medians;

    for (int instruction : *instructions) {
        if (instruction >= 0) {
            tree.insert(instruction);
        } else {
            if (!tree.isEmpty()) {
                // Assuming the definition of getMedian() method in AvlTree
                // This method would need to be implemented as part of AvlTree
                int median = tree.getMedian();
                medians.push_back(median);
                tree.remove(median);
            }
        }
    }

    // Print medians
    for (int median : medians) {
        std::cout << median << ' ';
    }
    std::cout << std::endl;
}
