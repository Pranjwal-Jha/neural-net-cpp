#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "randomizer.h"
#include "activation.h"
int main(){
    Matrix m1{4,3,1.0};
    m1.randomize();
    m1.PrintMat();
    Matrix m2 = m1.Transpose();
    m2.PrintMat();
    std::cout << std::endl;
    return 0;
}
// g++ main.cpp matrix.cpp activation.cpp -o main
