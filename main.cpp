#include "myVector.hpp"
#include "myList.hpp"
#include "myHeap.hpp"
#include "myAVLtree.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Cannot open file: " << inputFile << std::endl;
        return 1;
    }

    std::vector<int> instructions;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        int number;
        iss >> command;

        if (command == "insert") {
            if (iss >> number) { // Ensure that a number follows the "insert" command
                instructions.push_back(number);
            }
        } else if (command == "pop") {
            std::string medianCommand;
            if (iss >> medianCommand && medianCommand == "median") {
                instructions.push_back(-1); // Represent a pop median operation
            }
        }
    }

   
    vectorMedian(&instructions);
    std::cout<<std::endl;
    std::cout<<"-------------------------------------------------"<<"\n"<<"\n"<<"\n"<<std::endl;
    listMedian(&instructions);
    std::cout<<"-------------------------------------------------"<<"\n"<<"\n"<<"\n"<<std::endl;
    heapMedian(&instructions);
    std::cout<<"-------------------------------------------------"<<"\n"<<"\n"<<"\n"<<std::endl;
    treeMedian(&instructions);

    return 0;
}
