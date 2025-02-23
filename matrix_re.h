#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<double>> mat;
    size_t rows, cols;

public:
    // Constructors
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, double init_val);

    // Operator Overloads
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    // Element-wise operations
    Matrix ele_wise_product(const Matrix& other) const;

    // Utility functions
    void randomize(double min = -1.0, double max = 1.0);
    Matrix Transpose() const;
    void PrintMat() const;

    // Accessors
    const double& at(size_t irow, size_t icol) const;
    double& at(size_t irow, size_t icol);
    size_t GetRow() const;
    size_t GetCol() const;
};

#endif // MATRIX_H
