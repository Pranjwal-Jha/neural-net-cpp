#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "randomizer.h"
#include "activation.h"
#include "matrix.h"
int main(){
    Matrix m1{4,3};
    m1.randomize();
    m1.PrintMat();
    Matrix m2{3,4};
    m2.randomize();
    m2.PrintMat();
    Matrix m3 = m1*m2;
    m3.PrintMat();
    std::cout << std::endl;
    return 0;
}
