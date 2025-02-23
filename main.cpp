#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "randomizer.h"
#include "activation.h"
#include "nn.h"
int main(){
    Matrix matrix_1{50,4};
    matrix_1.randomize();
    NeuralNetwork newnn{matrix_1.GetSize()};
    Matrix output = newnn.forward(matrix_1);
    output.PrintMat();
    std::cout << std::endl;
    return 0;
}
// g++ main.cpp matrix.cpp activation.cpp -o main
// W (2×3):        X (3×2):        b (2×1):
// [1 2 3]         [1 4]           [1]
// [4 5 6]         [2 5]           [2]
//                 [3 6]

// Step 1 - W*X:
// [1*1 + 2*2 + 3*3    1*4 + 2*5 + 3*6]     =    [14  32]
// [4*1 + 5*2 + 6*3    4*4 + 5*5 + 6*6]          [32  77]

// Step 2 - Add bias (broadcasting b to each column):
// [14+1  32+1]    =    [15  33]
// [32+2  77+2]         [34  79]
