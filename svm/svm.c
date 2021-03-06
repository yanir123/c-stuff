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
    
    array* pred = array_argmax(scores, 1);
    free_array(scores);

    return pred;
}

array* svm_loss(array* weights, array* features, array* labels, double regularization) {
    double delta = 1.0;

    array* scores = dot_product(features, weights);
    array* correct_classes = array_at(scores, labels, 1);
    array* diff = array_sub(scores, correct_classes);
    array* diff_with_delta = array_add_single(diff, delta);
    free_array(diff);
    
    array* margins = array_maximum(diff_with_delta, 0);
    array_set(margins, labels, 0); 
    free_array(diff_with_delta);

    double loss = array_sum(margins);

    array* weights_t = array_transpose(weights);
    array* descent = dot_product(weights_t, weights);
    loss += 0.5 * regularization * array_sum(descent);
    free_array(weights_t);
    free_array(descent);

    array* mask = zero_array(margins->height, margins->width); 
    array* indexes = array_gt(mask, 0); //TODO: implement array_gt
    array_set(mask, indexes, 1);

    double count = array_sum(mask);
    array_set(mask, labels, -count);

    array* features_t = array_transpose(features);

    array* dw = dot_product(features_t, mask);
    array* dw_normalized = array_div_single(dw, mask->height);
    array* weights_reg = array_mul_single(weights, regularization);
    array* dw_reg = array_add(dw_normalized, weights_reg);

    free_array(dw_normalized);
    free_array(dw);
    free_array(weights_reg);
    free_array(features_t);
    free_array(indexes);
    free_array(mask);
    free_array(margins);
    free_array(scores);
    free_array(correct_classes);

    return dw_reg;
}