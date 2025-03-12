#ifndef NN_H
#define NN_H
#include <vector>
#include "matrix.h"
#include "activation.h"
#include "bceloss.h"
class NeuralNetwork{
private:
    std::vector<size_t> topology; // input layer feature(cols), hidden layer , output layer <- input in this form
    std::vector<Matrix> weights;
    std::vector<Matrix> bias;
    std::vector<Matrix> layer_outputs;
    std::vector<Matrix> layer_inputs;
    double learningRate;
public:
    NeuralNetwork(const std::vector<size_t>& inputsize,double learningRate=0.01)
        : topology(inputsize),learningRate(learningRate){
            if(inputsize.size()<2) throw std::invalid_argument("Topology must have atleast an input and output layer");
            for(size_t i=1;i<topology.size();i++){
                weights.push_back(Matrix(topology[i-1],topology[i]));
                weights.back().randomize();
                bias.push_back(Matrix(topology[i],1));
                bias.back().randomize();
            }
        }


    Matrix forward(const Matrix& input){
        layer_outputs.clear();
        layer_inputs.clear();
        layer_outputs.push_back(input);
        Matrix curr_output = input;
        for(size_t i=0;i<weights.size();i++){
            Matrix layer_output = curr_output*weights[i];
            for(size_t row=0;row<layer_output.GetRow();row++){
                for(size_t col=0;col<layer_output.GetCol();col++){
                    layer_output.at(row,col)+=bias[i].at(col,0);
                }
            }
            layer_inputs.push_back(layer_output);
            curr_output = Activation::sigmoid(layer_output);
            layer_outputs.push_back(curr_output);
        }
        return curr_output;
    }

    double train(const Matrix& input,const Matrix& output, bool printLoss){
        Matrix prediction = forward(input);
        // std::cout << "Passed first forward pass !" << std::endl;
        double loss=LossBCE::BCELoss(output,prediction);
        // std::cout << "Passed BCELoss Calculation !" << std::endl;
        if(printLoss){ //edit in the final push
            std::cout << "The Loss is : " << loss << std::endl;
        }
        Matrix gradient = LossBCE::BCEDerivative(output,prediction);
        // std::cout << "Passed BCELossDerivative Calculation !" << std::endl;
        for(int i=weights.size()-1;i>=0;i--){
            // std::cout << "Gradient Dimension : " << gradient.GetRow() << "," << gradient.GetCol() << " Layer input : " << i << " Size " << layer_inputs[i].GetRow() << "," << layer_inputs[i].GetCol() << std::endl;
            gradient=gradient.ele_wise_product(Activation::sigmoid_drv(layer_inputs[i])); //erroring out here
            // std::cout << "Passed element wise product Calculation !" << std::endl;
            Matrix weight_gradient = layer_outputs[i].Transpose()*gradient;
            // std::cout << "Passed weight gradient Calculation !" << std::endl;
            Matrix bias_gradient(bias[i].GetRow(),bias[i].GetCol());
            // std::cout << "Passed bias gradient Calculation !" << std::endl;
            for(size_t col=0;col<gradient.GetCol();col++){
                double sum=0.0;
                for(size_t row=0;row<gradient.GetRow();row++){
                    sum+=gradient.at(row,col); //since the bias is common for a row hence we sum all those gradients up.
                }
                bias_gradient.at(col,0)=sum;
            }
            if(i>0){
                gradient=gradient*weights[i].Transpose();
            }
            for(size_t row=0;row<weights[i].GetRow();row++){
                for(size_t col=0;col<weights[i].GetCol();col++){
                    weights[i].at(row,col)-=learningRate*weight_gradient.at(row,col);
                }
            }
            for(size_t row=0;row<bias[i].GetRow();row++){
                bias[i].at(row,0)-=learningRate*bias_gradient.at(row,0);
            }
        }
        return loss;
    }
    void fit(const Matrix& input,const Matrix& target, size_t epochs,bool printLoss=true,size_t print_interval=100){
        for(size_t epoch=0;epoch<epochs;epoch++){
            double loss=train(input,target,false);
            if(printLoss && (epoch%print_interval==0 || epoch==epochs-1)){
                std::cout << "Epoch : " << epoch << " Loss : " << loss << std::endl;
            }
        }
        // std::cout << "Passed training phase !" << std::endl;
        if(printLoss && false){
            Matrix finalPredictions=forward(input);
            std::cout << "Final Prediction: " << std::endl;
            finalPredictions.PrintMat();
        }
    }
    double evaluate(const Matrix& input,const Matrix& target,double threshold=0.5){
        Matrix predictions=forward(input);
        int correct=0;
        int total=target.GetRow()*target.GetCol();
        for(size_t row=0;row<target.GetRow();row++){
            for(size_t col=0;col<target.GetCol();col++){
                bool prediction=predictions.at(row,col)>=threshold;
                bool actual=target.at(row,col)>=threshold;
                if(prediction==actual){
                    correct++;
                }
            }
        }
        return static_cast<double>(correct)/total;
    }
};
#endif
