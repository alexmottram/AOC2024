#include  <iostream>
#include "utils/utils.h"

int main()
{
    std::cout << "Use case testing of arrays!" << std::endl;
    utils::Array2D<int> array{{
            {1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            }
    };
    std::cout << "Original array: " << std::endl << array;

    for (auto& x: array) {
        if (x%2==0){
            x = 2*x;
        }
    }
    std::cout << "Array after doubling all even numbers: " << std::endl << array;

    return 0;
}