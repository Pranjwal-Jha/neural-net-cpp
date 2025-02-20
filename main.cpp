#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include "randomizer.h"

class Matrix{
private:
    std::vector<std::vector<double>> mat;
    size_t rows, cols;

public:
    Matrix(size_t rows, size_t cols)
    : rows(rows), cols(cols){
        mat.resize(rows,std::vector<double>(cols,0.0));
    }
    //constructor with initialisation
    Matrix(size_t rows,size_t cols,double init_val)
    :   rows(rows),cols(cols)
    {
        mat.resize(rows,std::vector<double>(cols,init_val));
    }
    Matrix operator+(const Matrix& other) const{
        if(cols!=other.cols || rows!=other.rows){
            throw std::invalid_argument("Invalid Addition Between two Matrices");
        }
        Matrix result(rows,cols,0.0);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                result.mat[i][j]=mat[i][j]+other.mat[i][j];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const{
        if(cols!=other.rows){
            throw std::invalid_argument("Invalid Multiplication between two Matrices");
        }
        Matrix result(rows,other.cols,0.0);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<other.cols;j++){
                for(size_t k=0;k<cols;k++){
                    result.mat[i][j]+=mat[i][k]*other.mat[k][j];
                }
            }
        }
        return result;
    }
    void randomize(double min=-1.0,double max=1.0){ //NN default
        std::uniform_real_distribution<double> unum(min,max);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                mat[i][j] = unum(NRandom::mt);
            }
        }
    }
    void PrintMat(){
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                std::cout << mat[i][j] << " ";
            }
            std::cout << '\n';
        }
        std::cout << std::endl;
    }
    //Getters for rows and columns
    size_t GetRow(){
        return rows;
    }
    size_t GetCol(){
        return cols;
    }
};

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
