#pragma once
#include "utils/utils.h"

// double svm_regressor(double** features, double* labels, double** weights, double* biases);
void svm_regressor_train(double** features, double* labels, double** weights, double* biases);
void svm_regressor_predict(double** features, double* predict_label);
void svm_regressor_loss(double** features, double* labels, double** weights, double* biases);
