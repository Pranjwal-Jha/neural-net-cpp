#ifndef Loss
#define Loss
#include "matrix.h"
#include <math.h>
#include <cmath>
//ctrl k + z to wrap around
namespace LossBCE{
    double BCELoss(const Matrix& y_true,const Matrix& y_pred){
        if (y_true.GetRow()!=y_pred.GetRow() || y_true.GetCol()!=y_pred.GetCol()){
            throw std::invalid_argument("Error in file bceloss.h, Dimension of y_pred & y_true are not same");
        }
        const double epsilon=1e-8;
        double sum_loss=0;
        double count=0;
        for(size_t i=0;i<y_true.GetRow();i++){
            for(size_t j=0;j<y_true.GetCol();j++){
                double pred=std::max(std::min(y_pred.at(i,j),1.0-epsilon),epsilon);
                sum_loss+=-1.0*(y_true.at(i,j)*std::log(pred) + (1.0-y_true.at(i,j))*std::log(1.0-pred));
                count++;
            }
        }
        return sum_loss/count;
    }

    Matrix BCEDerivative(const Matrix& y_true,const Matrix& y_pred){
        if (y_true.GetRow()!=y_pred.GetRow() || y_true.GetCol()!=y_pred.GetCol()){
            throw std::invalid_argument("Error in file bceloss.h, Dimension of y_pred & y_true are not same");
        }
        Matrix gradient(y_true.GetRow(),y_pred.GetRow());
        const double epsilon=1e-8;
        for(size_t i=0;i<y_true.GetRow();i++){
            for(size_t j=0;j<y_true.GetCol();j++){
                double pred=std::max(std::min(y_pred.at(i,j),1.0-epsilon),epsilon);
                gradient.at(i,j)=-1.0*y_true.at(i,j)/pred + (1.0-y_true.at(i,j))/(1.0-pred);
            }
        }
        double normalise_factor = 1.0/static_cast<double>(y_true.GetRow()*y_true.GetCol());
        for(size_t i=0;i<gradient.GetRow();i++){
            for(size_t j=0;j<gradient.GetCol();j++){
                gradient.at(i,j)*=normalise_factor;
            }
        }
        return gradient;
    }
}
#endif
