// myHeap.cpp
#include "myHeap.hpp"


void heapMedian(const std::vector<int>* instructions) {
    std::priority_queue<int> small;  // Max heap to store the smaller half of the elements
    std::priority_queue<int, std::vector<int>, std::greater<int>> large; // Min heap to store the larger half of the elements
    std::vector<int> medians;  // Vector to store the medians for later printing

    // Iterate through each instruction in the instructions vector
    for (int instr : *instructions) {
        if (instr >= 0) {
            // If the instruction is a non-negative integer, treat it as an insert operation
            
            // Insert into the small max heap if it's empty or the value is less than or equal to the top of small
            if (small.empty() || instr <= small.top()) {
                small.push(instr);
            } else {
                // Otherwise, insert into the large min heap
                large.push(instr);
            }

            // Balance the heaps to ensure the size property
            if (small.size() > large.size() + 1) {
                // If small has more than one extra element, move the top element to large
                large.push(small.top());
                small.pop();
            } else if (large.size() > small.size()) {
                // If large has more elements, move the top element to small
                small.push(large.top());
                large.pop();
            }
        } else {
            // If the instruction is negative, treat it as a request to pop and print the median
            
            // Ensure small isn't empty before attempting to pop the median
            if (!small.empty()) {
                medians.push_back(small.top()); // Save the top of small as the median
                // If small has more than one extra element compared to large, just pop from small
                if (small.size() > large.size()) {
                    small.pop();
                } else {
                    // If the heaps are balanced in size, pop from small and balance the heaps
                    small.pop(); // Pop first to maintain the heap property
                    small.push(large.top()); // Move the smallest element from large to small
                    large.pop();
                }

                // Rebalance the heaps if large ends up larger than small
                if (small.size() < large.size()) {
                    small.push(large.top());
                    large.pop();
                }
            }
        }
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> duration = end - start;
    // std::cout << "Heap duration: " << duration.count() << "ms\n";

    // Output all medians at once
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
