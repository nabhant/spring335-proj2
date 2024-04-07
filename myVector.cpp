#include "myVector.hpp"

// void vectorMedian (const std::vector<int> * instructions){
//     std::vector<int> result;
//     int current_Median; 
//     for (int instr: *instructions){
//         if (instr >= 0){

//             // INSERT
//             auto it = std::lower_bound(result.begin(), result.end(), instr);
//             result.insert(it, instr);
//         } 
        
//         else{

//             //POP MEDIAN
//             if(!result.empty()){
//                 size_t medianIndex = (result.size() - 1 ) / 2;
//                 result.erase(result.begin() + medianIndex);
//             }
//         }
//     }

//      for (int median : result) {
//         std::cout << median << " ";
//     }
//     std::cout << std::endl;
// }

void vectorMedian(const std::vector<int>* instructions) {
    std::vector<int> data; // Vector to keep the elements sorted
    std::vector<int> medians; // Vector to store medians before printing
    
    for (const int instr : *instructions) {
        if (instr >= 0) {
            // Insert operation using iterators
            std::vector<int>::iterator it = std::lower_bound(data.begin(), data.end(), instr);
            data.insert(it, instr);
        } else {
            // Pop median operation
            if (!data.empty()) {
                std::vector<int>::size_type medianIndex = (data.size() - 1) / 2; // Handle both even and odd sizes
                std::vector<int>::iterator medianIt = data.begin() + medianIndex;
                medians.push_back(*medianIt); // Save median for later printing
                data.erase(medianIt); // Remove median from data
            }
        }
    }

    // Print out the medians after completing all operations
    for (int median : medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}