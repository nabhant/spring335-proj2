#include "myVector.hpp"

void vectorMedian (const std::vector<int> * instructions){
    std::vector<int> result;
    int current_Median; 
    for (int instr: *instructions){
        if (instr >= 0){

            // INSERT
            auto it = std::lower_bound(result.begin(), result.end(), instr);
            result.insert(it, instr);
        } 
        
        else{

            //POP MEDIAN
            if(!result.empty()){
                size_t medianIndex = (result.size() - 1 ) / 2;
                result.erase(result.begin() + medianIndex);
            }
        }
    }

     for (int median : result) {
        std::cout << median << " ";
    }
    std::cout << std::endl;
}
