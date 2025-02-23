#ifndef MATRIX_H
#define  MATRIX_H
#include <iostream>
#include <vector>
#include <random>
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
    Matrix operator-(const Matrix& other) const{
        if(cols!=other.cols || rows!=other.rows){
            throw std::invalid_argument("Invalid Addition Between two Matrices");
        }
        Matrix result(rows,cols,0.0);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                result.mat[i][j]=mat[i][j]-other.mat[i][j];
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
    Matrix ele_wise_product(const Matrix& other)const{
        if(cols!=other.cols || rows!=other.rows){
            throw std::invalid_argument("Invalid Addition Between two Matrices");
        }
        Matrix result(rows,cols);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                result.mat[i][j] = mat[i][j]*other.mat[i][j];
            }
        }
        return result;
    }
    Matrix Transpose() const{
        Matrix result(cols,rows);
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                result.mat[j][i] = mat[i][j];
            }
        }
        return result;
    }
    void PrintMat() const{
        for(size_t i=0;i<rows;i++){
            for(size_t j=0;j<cols;j++){
                std::cout << mat[i][j] << " ";
            }
            std::cout << '\n';
        }
        std::cout << std::endl;
    }
    const double& at(size_t irow,size_t icol) const{
        if(irow>rows || icol>cols){
            throw std::invalid_argument("Indices out of range!");
        }
        return mat[irow][icol];
    }
    double& at(size_t irow,size_t icol){
        if(irow>rows || icol>cols){
            throw std::invalid_argument("Indices out of range!");
        }
        return mat[irow][icol];
    }
    //Getters for rows and columns
    size_t GetRow() const{
        return rows;
    }
    size_t GetCol() const{
        return cols;
    }
    size_t GetSize() const{
        return GetCol();
    }
};


#endif
