#include "myVector.hpp"

void vectorMedian(const std::vector<int>* instructions) {
    std::vector<int> data; // Initializes a vector to keep elements in sorted order
    std::vector<int> medians; // Initializes a vector to store medians before printing
    
    // Iterate over each instruction in the provided vector
    for (const int instr : *instructions) {
        if (instr >= 0) {
            // If the instruction is a non-negative integer, treat it as an insert operation
            
            // Use std::lower_bound to find the correct position in the sorted vector for the new element
            // This maintains the sorted order efficiently
            std::vector<int>::iterator it = std::lower_bound(data.begin(), data.end(), instr);
            // Insert the new element at the position returned by std::lower_bound
            data.insert(it, instr);
        } else {    // If the instruction is negative, treat it as a request to pop and print the median
            
            // Ensure the vector is not empty before attempting to find and remove the median
            if (!data.empty()) {
                // Calculate the index of the median element
                // For an even number of elements, this results in the lower median
                std::vector<int>::size_type medianIndex = (data.size() - 1) / 2;
                // Use the calculated index to find the iterator to the median element
                std::vector<int>::iterator medianIt = data.begin() + medianIndex;
                // Store the median value in the 'medians' vector for later printing
                medians.push_back(*medianIt);
                // Remove the median element from 'data'
                data.erase(medianIt);
            }
        }
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> duration = end - start;
    
    // std::cout << "Vector duration: " << duration.count() << "ms\n";

    // Print out the medians after completing all operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}