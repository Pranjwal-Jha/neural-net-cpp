#include <iostream>
#include <vector>
#include "matrix.h"
#include "nn.h"
#include "activation.h"

// Function to create a synthetic XOR dataset
std::pair<Matrix, Matrix> create_xor_dataset() {
    // XOR input: (0,0), (0,1), (1,0), (1,1)
    std::vector<std::vector<double>> inputs = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    // XOR output: 0, 1, 1, 0
    std::vector<std::vector<double>> outputs = {
        {0},
        {1},
        {1},
        {0}
    };

    return {Matrix(inputs), Matrix(outputs)};
}

void test_xor() {
    std::cout << "========== XOR PROBLEM TEST ==========" << std::endl;

    // Create XOR dataset
    auto [X, y] = create_xor_dataset();

    std::cout << "Input data:" << std::endl;
    X.PrintMat();

    std::cout << "Target output:" << std::endl;
    y.PrintMat();

    // Create neural network with topology [2, 4, 1]
    // (2 input features, 4 hidden neurons, 1 output neuron)
    NeuralNetwork nn({2, 4, 1}, 0.1);

    // Train the model
    std::cout << "Training the model..." << std::endl;
    nn.fit(X, y, 10000, true, 1000);

    // Test the trained model
    std::cout << "\nPredictions after training:" << std::endl;
    Matrix predictions = nn.forward(X);
    predictions.PrintMat();

    // Calculate accuracy
    double accuracy = nn.evaluate(X, y);
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;
}

int main() {
    // Test XOR problem
    test_xor();

    return 0;
}
