#ifndef NN_H
#define NN_H
#include <vector>
#include "matrix.h"
#include "activation.h"
class NeuralNetwork{
private:
    // std::vector<size_t> topology; // to use the input size, hidden size and output size
    Matrix weights;
    Matrix bias;
public:
    NeuralNetwork(size_t inputsize)
        : weights(1,inputsize),bias(1,1){
            weights.randomize();
            bias.randomize();
        }
    Matrix forward(const Matrix& input){
        Matrix output = input*weights.Transpose();
        for(size_t rows=0;rows<output.GetRow();rows++){
            output.at(rows,0)+=bias.at(0,0);
        }
        return Activation::sigmoid(output);
    }
};
#endif
