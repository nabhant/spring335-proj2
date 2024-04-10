// #include "myAVLtree.hpp"
// #include <vector>
// #include <iostream>


// void AvlTree::treeMedian(const std::vector<int>* instructions) {
//     AvlTree small;
//     AvlTree large;

//     std::vector<int> medians;

//     auto start = std::chrono::high_resolution_clock::now();

//     int small_size = 0, large_size = 0;

//     for (auto it = instructions->begin(); it != instructions->end(); ++it)
//     {
//         if (*it != -1)
//         {
//             if (small.isEmpty() || *it <= small.findMax())
//             {
//                 small.insert(*it);
//                 small_size++;
//             }
//             else
//             {
//                 large.insert(*it);
//                 large_size++;
//             }

//             while (small_size > large_size + 1)
//             {
//                 large.insert(small.findMax());
//                 large_size++;

//                 small.remove(small.findMax());
//                 small_size--;
//             }

//             while (large_size > small_size)
//             {
//                 small.insert(large.findMin());
//                 small_size++;

//                 large.remove(large.findMin());
//                 large_size--;
//             }
//         }
//         else
//         {
//             medians.push_back(small.findMax());
//             small.remove(small.findMax());
//             small_size--;

//             while (small_size < large_size)
//             {
//                 small.insert(large.findMin());
//                 small_size++;

//                 large.remove(large.findMin());
//                 large_size--;
//             }
//         }
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> duration = end - start;

//     for (int median : medians)
//     {
//         std::cout << median << " ";
//     }
//     std::cout << "\n";

//     // std::cout << "Algorithm duration: " << duration.count() << "ms\n";
// }
