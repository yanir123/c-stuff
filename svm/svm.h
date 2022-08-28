#pragma once
#include "../utils/utils.h"

struct svm_classifier {
    array* weights;
} typedef svm_classifier;

svm_classifier* svc_fit(array* features, array* labels, uint8_t num_classes, double learning_rate, double regularization);
array* svm_loss(array* weights, array* features, array* labels, double regularization);
array* svc_predict(svm_classifier* svc, array* test);