#include <cmath>
#include "matrix.h"
namespace Activation{
    //Should i make function static or not  ???
    Matrix ReLu(const Matrix& input){
        Matrix result(input.GetRow(),input.GetCol());
        for(size_t i=0;i<input.GetRow();i++){
            for(size_t j=0;j<input.GetCol();j++){
                result.at(i,j) = std::max(0.0,input.at(i,j));
            }
        }
        return result;
    }
    Matrix relu_drv(const Matrix& input){
        Matrix result(input.GetRow(),input.GetCol());
        for(size_t i=0;i<input.GetRow();i++){
            for(size_t j=0;j<input.GetCol();j++){
                result.at(i,j) = input.at(i,j) > 0 ? 1.0 : 0.0;
            }
        }
        return result;
    }
    Matrix sigmoid(const Matrix& input){
        Matrix result(input.GetRow(),input.GetCol());
        for(size_t i=0;i<input.GetRow();i++){
            for(size_t j=0;j<input.GetCol();j++){
                result.at(i,j) = 1.0/(1.0 + std::exp(-input.at(i,j)));
            }
        }
        return result;
    }
    Matrix sigmoid_drv(const Matrix& input){
        Matrix s = sigmoid(input);
        Matrix ones(input.GetRow(),input.GetCol(),1.0);
        // std::cout << "Sigmoid derivative completed !" << std::endl;
        return s.ele_wise_product(ones-s);
    }
}
