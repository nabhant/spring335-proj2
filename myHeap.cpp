// myHeap.cpp
#include "myHeap.hpp"


void heapMedian(const std::vector<int>* instructions) {
    std::priority_queue<int> small; // Max heap for the smaller half
    std::priority_queue<int, std::vector<int>, std::greater<int>> large; // Min heap for the larger half
    std::vector<int> medians; // Store medians here

    for (int instr : *instructions) {
        if (instr >= 0) {
            // Insert operation
            if (small.empty() || instr <= small.top()) {
                small.push(instr);
            } else {
                large.push(instr);
            }

            // Rebalance heaps if necessary
            if (small.size() > large.size() + 1) {
                large.push(small.top());
                small.pop();
            } else if (large.size() > small.size()) {
                small.push(large.top());
                large.pop();
            }
        } else {
            // Pop median operation
            if (!small.empty()) {
                medians.push_back(small.top());
                if (small.size() > large.size()) {
                    small.pop();
                } else {
                    // Move the top element from large to small after popping from small,
                    // to maintain the property that small has the same number or one more element than large.
                    small.pop();
                    small.push(large.top());
                    large.pop();
                }
                
                // After removing the median, rebalance if necessary
                if (small.size() < large.size()) {
                    small.push(large.top());
                    large.pop();
                }
            }
        }
    }

    // Output all medians at once
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
