// #include "myAVLtree.hpp"
// #include <vector>
// #include <iostream>


// void AvlTree::treeMedian(const std::vector<int>* instructions){
//     AvlTree small;
//     AvlTree large;

//     std::vector<int> medians;

//     auto start = std::chrono::high_resolution_clock::now();

//     int smaller = 0, larger = 0;

//     for (auto it = instructions->begin(); it != instructions->end(); ++it){
//         if (*it != -1){
//             if (small.isEmpty() || *it <= small.findMax()){
//                 small.insert(*it);
//                 smaller++;
//             }
//             else{
//                 large.insert(*it);
//                 larger++;
//             }

//             while (smaller > larger + 1){
//                 large.insert(small.findMax());
//                 larger++;

//                 small.remove(small.findMax());
//                 smaller--;
//             }

//             while (larger > smaller){
//                 small.insert(large.findMin());
//                 smaller++;

//                 large.remove(large.findMin());
//                 larger--;
//             }
//         }
//         else{
//             medians.push_back(small.findMax());
//             small.remove(small.findMax());
//             smaller--;

//             while (smaller < larger){
//                 small.insert(large.findMin());
//                 smaller++;

//                 large.remove(large.findMin());
//                 larger--;
//             }
//         }
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> duration = end - start;

//     for (int median : medians){
//         std::cout << median << " ";
//     }
//     std::cout << "\n";

//     // std::cout << "Algorithm duration: " << duration.count() << "ms\n";
// }
