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

// Function to create a synthetic binary classification dataset
std::pair<Matrix, Matrix> create_binary_classification_dataset(int num_samples = 100) {
    std::vector<std::vector<double>> inputs;
    std::vector<std::vector<double>> outputs;
    
    // Generate random data points with 2 features
    for (int i = 0; i < num_samples; i++) {
        // Generate random x and y between 0 and 1
        double x = NRandom::mt() / (double)std::mt19937::max();
        double y = NRandom::mt() / (double)std::mt19937::max();
        
        // Class is 1 if x + y > 1, otherwise 0 (simple diagonal split)
        double label = (x + y > 1.0) ? 1.0 : 0.0;
        
        inputs.push_back({x, y});
        outputs.push_back({label});
    }
    
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

void test_binary_classification() {
    std::cout << "\n========== BINARY CLASSIFICATION TEST ==========" << std::endl;
    
    // Create a synthetic binary classification dataset
    auto [X, y] = create_binary_classification_dataset(50);
    
    std::cout << "Sample of input data (first 5 rows):" << std::endl;
    for (size_t i = 0; i < 5 && i < X.GetRow(); i++) {
        for (size_t j = 0; j < X.GetCol(); j++) {
            std::cout << X.at(i, j) << " ";
        }
        std::cout << " -> " << y.at(i, 0) << std::endl;
    }
    
    // Create neural network with topology [2, 5, 3, 1]
    // (2 input features, two hidden layers, 1 output neuron)
    NeuralNetwork nn({2, 5, 3, 1}, 0.05);
    
    // Train the model
    std::cout << "Training the model..." << std::endl;
    nn.fit(X, y, 5000, true, 500);
    
    // Calculate accuracy
    Matrix predictions = nn.forward(X);
    double accuracy = nn.evaluate(predictions, y, 0.5);
    std::cout << "Final accuracy: " << accuracy * 100 << "%" << std::endl;
}

int main() {
    // Fix for evaluate function by swapping input and target (temporary solution)
    // Since we found an issue with the evaluate function in the original code
    
    // Test XOR problem
    test_xor();
    
    // Test binary classification
    test_binary_classification();
    
    return 0;
}
