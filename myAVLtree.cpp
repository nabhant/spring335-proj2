#include "myAVLtree.hpp"

void treeMedian(const std::vector<int> *instructions) {

    // Initialize two AVL Trees: one to store the smaller half and another for the larger half of the numbers
    AvlTree<int> smallTree;
    AvlTree<int> largeTree;

    // Vector to store the medians after each removal instruction (-1)
    std::vector<int> medians;

    auto start = std::chrono::high_resolution_clock::now();

    // Iterate over each instruction in the input vector
    for (int instr: *instructions) {

        // Check if the instruction is to remove (-1) the current median
        if (instr == -1) {
            if (!smallTree.isEmpty()) {

                // Find the largest element in the smallTree, which is the current median
                medians.push_back(smallTree.findMax());
                smallTree.remove(smallTree.findMax());

                // Balance the two trees if necessary (ensuring size property)
                if (smallTree.size() < largeTree.size()) {
                    // Move the smallest element from the largeTree to the smallTree
                    smallTree.insert(largeTree.findMin());
                    largeTree.remove(largeTree.findMin());
                }
            }
        } else {
            // If the instruction is not -1, it's an insertion of a new value

            // If smallTree is empty or the new value is less than or equal to the max of smallTree
            if (smallTree.isEmpty() || instr <= smallTree.findMax()) {
                smallTree.insert(instr);
            } else {
                largeTree.insert(instr);
            }

            // Balance the trees after each insertion to maintain the properties of the median finding algorithm
            if (smallTree.size() > largeTree.size() + 1) {

                // If smallTree is more than one larger than largeTree, balance by moving the max from small to large
                largeTree.insert(smallTree.findMax());
                smallTree.remove(smallTree.findMax());
            } else if (largeTree.size() > smallTree.size()) {

                // If largeTree is larger, balance by moving the min from large to small
                smallTree.insert(largeTree.findMin());
                largeTree.remove(largeTree.findMin());
            }
        }
    }


    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    for (int median: medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
    std::cout << "Tree duration: " << duration.count() << "ms\n";


}

