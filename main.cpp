#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "randomizer.h"
#include "activation.h"
#include "nn.h"
int main(){
    Matrix data({{1,2,3},{4,5,6},{7,8,9}});
    std::vector<std::vector<double>> a = {{0.283185}, {0.64159}, {1.0}}; //Double braces needed
    Matrix mul(a);
    // std::cout << mul.GetRow();
    // std::cout << "hello";
    // std::cout << data.GetCol();
    Matrix ans = data*mul;
    // data.PrintMat();
    // mul.PrintMat();
    ans.PrintMat();
    std::cout << std::endl;
    return 0;
}
// g++ main.cpp matrix.cpp activation.cpp -o main
