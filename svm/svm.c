#include "svm.h"

// TODO: implement the svmm classifier

svm_classifier* svc_fit(array* features, array* labels, uint8_t num_classes, double learning_rate, double regularization) {
    array* weights = random_array(features->width, num_classes, 1e-3, 1e-4);

    array* gradients = svm_loss(weights, features, labels, regularization);

    array* scaled_grads = array_mul_single(gradients, learning_rate);
    free_array(gradients);
    array* new_weights = array_sub(weights, scaled_grads);
    free_array(weights);
    free_array(scaled_grads);

    svm_classifier* classifier = malloc(sizeof(svm_classifier));

    classifier->weights = new_weights;
}

array* svc_predict(svm_classifier* svc, array* test) {
    array* scores = dot_product(test, svc->weights);
    
    array* pred = array_argmax(scores, 1); // TODO: implement array_argmax
    free_array(scores);

    return pred;
}

array* svm_loss(array* weights, array* features, array* labels, double regularization) {
    // TODO: implement svm loss function
}