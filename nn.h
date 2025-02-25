 #ifndef NN_H
#define NN_H
#include <vector>
#include "matrix.h"
#include "activation.h"
class NeuralNetwork{
private:
    std::vector<size_t> topology; // input layer feature(cols), hidden layer , output layer <- input in this form
    std::vector<Matrix> weights;
    std::vector<Matrix> bias;
public:
    NeuralNetwork(const std::vector<size_t>& inputsize)
        : topology(inputsize){
            if(inputsize.size()<2) throw std::invalid_argument("Topology must have atleast an input and output layer");
            for(size_t i=1;i<topology.size();i++){
                weights.push_back(Matrix(topology[i-1],topology[i]));
                weights.back().randomize();
                bias.push_back(Matrix(topology[i],1));
                bias.back().randomize();
            }
        }


    Matrix forward(const Matrix& input){
        Matrix curr_output = input;
        for(size_t i=0;i<weights.size();i++){
            Matrix layer_output = curr_output*weights[i];
            for(size_t row=0;row<layer_output.GetRow();row++){
                for(size_t col=0;col<layer_output.GetCol();col++){
                    layer_output.at(row,col)+=bias[i].at(col,0);
                }
            }
            curr_output = Activation::sigmoid(layer_output);
        }
        return curr_output;
    }
};
#endif
