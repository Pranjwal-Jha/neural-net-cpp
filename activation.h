#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "matrix.h"

namespace Activation {
    Matrix ReLu(const Matrix& input);
    Matrix relu_drv(const Matrix& input);
    Matrix sigmoid(const Matrix& input);
    Matrix sigmoid_drv(const Matrix& input);
}

#endif
