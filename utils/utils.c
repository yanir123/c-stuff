#include "utils.h"

void swap(uint32_t* a, uint32_t* b) 
{ 
    uint32_t t = *a; 
    *a = *b; 
    *b = t; 
} 
  
int partition (double values[], uint32_t arr[], int low, int high) 
{ 
    double pivot = values[arr[high]];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++) 
    { 
        if (values[arr[j]] < pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(double values[], uint32_t arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(values, arr, low, high); 
  
        quickSort(values, arr, low, pi - 1); 
        quickSort(values, arr, pi + 1, high);
    } 
} 

array* dot_product(array first, array second) {
    array* output = malloc(sizeof(array));
    output->height = first.height;
    output->width = second.width;
    output->values = malloc(sizeof(double**) * first.height);
    
    #pragma omp parallel for
    for (uint32_t i = 0; i < first.height; i++) {
        output->values[i] = malloc(sizeof(double) * second.width);
        for (uint32_t j = 0; j < second.width; j++) {
            double sum = 0;
            for (uint32_t k = 0; k < first.width; k++) { // First width or second height
                sum += first.values[i][k] * second.values[k][j];
            }
            output->values[i][j] = sum;
        }
    }

    return output;
}

array* random_array(uint32_t height, uint32_t width, double max_rand, double min_rand) {
    array* arr = zero_array(height, width);

    #pragma omp parallel for
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr->values[i][j] = random_double(max_rand, min_rand);
        }
    }

    return arr;
}

array* zero_array(uint32_t height, uint32_t width) {
    array* arr = malloc(sizeof(array));
    arr->height = height;
    arr->width = width;
    arr->values = malloc(sizeof(double*) * height);

    #pragma omp parallel for
    for (int i = 0; i < height; i++) {
        arr->values[i] = calloc(width, sizeof(double));
    }

    return arr;
}

void free_array(array* arr) {

    #pragma omp parallel for
    for (int i = 0; i < arr->height; i++) {
        free(arr->values[i]);
    }
    
    free(arr->values);
    free(arr);
}

double random_double(double max, double min) {
    return (double)rand() / RAND_MAX * max + min;
}

int array_agg_other(array const* first, array const* second, double (*f)(double, double)) {
    if ((second->height != 1 && (second->height != first->height || second->width != first->width)) || 
        (second->height == 1 && second->width != first->height)) {
        return 0;
    }

    if (second->height == 1) {
        #pragma omp parallel for
        for (int i = 0; i < second->width; i++) {
            for (int j = 0; j < first->width; j++) {
                first->values[i][j] = f(first->values[i][j], second->values[0][i]);
            }
        }
    } else {
        #pragma omp parallel for
        for (int i = 0; i < first->height; i++) {
            for (int j = 0; j < first->width; j++) {
                first->values[i][j] = f(first->values[i][j], second->values[i][j]);
            }
        }
    }

    return 1;
}

void array_agg_self(array const* first, double (*f)(double)) {
    #pragma omp parallel for
    for (int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            first->values[i][j] = f(first->values[i][j]);
        }
    }
}

void array_agg_rvalue(array const* first, double second, double (*f)(double, double)) {
    #pragma omp parallel for
    for (int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            first->values[i][j] = f(first->values[i][j], second);
        }
    }
}

double sub(double first, double second) {
    return first - second;
}

double add(double first, double second) {
    return first + second;
}

double mul(double first, double second) {
    return first * second;
}

double divide(double first, double second) {
    return first / second;
}

double power(double first, double second) {
    return pow(first, second);
}

double exponent(double first) {
    return exp(first);
}

double square_root(double first) {
    return sqrt(first);
}

double logarithm(double first) {
    return log(first);
}

int array_sub(array const* first, array const* second) {
    return array_agg_other(first, second, sub);
}

int array_add(array const* first, array const* second) {
    return array_agg_other(first, second, add);
}

int array_mul(array const* first, array const* second) {
    return array_agg_other(first, second, mul);
}

int array_div(array const* first, array const* second) {
    return array_agg_other(first, second, divide);
}

int array_pow(array const* first, array const* second) {
    return array_agg_other(first, second, power);
}

void array_pow_single(array const* first, double second) {
    array_agg_rvalue(first, second, power);
}

void array_sub_single(array const* first, double second) {
    array_agg_rvalue(first, second, sub);
}

void array_add_single(array const* first, double second) {
    array_agg_rvalue(first, second, add);
}

void array_mul_single(array const* first, double second) {
    array_agg_rvalue(first, second, mul);
}

void array_div_single(array const* first, double second) {
    array_agg_rvalue(first, second, divide);
}

void array_print(array* arr) {
    for (int i = 0; i < arr->height; i++) {
        printf("{ ");
        for (int j = 0; j < arr->width; j++) {
            printf("%f ", arr->values[i][j]);
        }
        printf("}\n");
    }
    printf("\n");
}

void array_sqrt(array const* first) {
    array_agg_self(first, square_root);
}

void array_exp(array const* first) {
    array_agg_self(first, exponent);
}

void array_log(array const* first) {
    array_agg_self(first, logarithm);
}