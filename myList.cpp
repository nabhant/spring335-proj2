// myList.cpp
#include "myList.hpp"

void listMedian(const std::vector<int>* instructions) {
    std::list<int> data; // Initializes a linked list to maintain a sorted sequence of integers
    std::vector<int> medians; // Initializes a vector to store the medians for later printing

    // Iterate over each instruction in the provided vector
    for (int instr : *instructions) {
        if (instr >= 0) {
            // If the instruction is a non-negative integer, treat it as an insert operation
            
            // Find the correct position in the sorted list for the new element
            auto it = data.begin();
            while (it != data.end() && *it < instr) {
                ++it;
            }
            // Insert the new element in the sorted position to maintain order
            data.insert(it, instr);
        } else {
            // If the instruction is negative, treat it as a request to pop and print the median
            
            // Check if the list is not empty
            if (!data.empty()) {
                auto it = data.begin();
                // Advance the iterator to point to the median element
                // For an even number of elements, this will be the lower median
                std::advance(it, (data.size() - 1) / 2);
                // Add the median value to the medians vector
                medians.push_back(*it);
                // Remove the median element from the list
                data.erase(it);
            }
        }
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> duration = end - start;
    // std::cout << "List duration: " << duration.count() << "ms\n";

    // Print out the medians after completing all operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
