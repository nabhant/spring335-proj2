// myList.cpp
#include "myList.hpp"

void listMedian(const std::vector<int>* instructions) {
    std::list<int> data; // Linked list to keep elements sorted
    std::vector<int> medians; // Vector to store medians before printing
    
    for (int instr : *instructions) {
        if (instr >= 0) {
            // Insert operation: Find the correct position and insert
            auto it = std::find_if(data.begin(), data.end(), [instr](const int& value) { return instr <= value; });
            data.insert(it, instr);
        } else {
            // Pop median operation
            if (!data.empty()) {
                auto it = data.begin();
                std::advance(it, (data.size() - 1) / 2); // Move iterator to median
                medians.push_back(*it); // Save median for later printing
                data.erase(it); // Remove the median
            }
        }
    }

    // Print out the medians after completing all operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
