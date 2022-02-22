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

array* dot_product(array const* first, array const* second) {
    array* output = malloc(sizeof(array));
    output->height = first->height;
    output->width = second->width;
    output->values = malloc(sizeof(double**) * first->height);
    
    #pragma omp parallel for
    for (uint32_t i = 0; i < first->height; i++) {
        output->values[i] = malloc(sizeof(double) * second->width);
        for (uint32_t j = 0; j < second->width; j++) {
            double sum = 0;
            for (uint32_t k = 0; k < first->width; k++) { // First width or second height
                sum += first->values[i][k] * second->values[k][j];
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

array* array_agg_other(array const* first, array const* second, double (*f)(double, double)) {
    if ((second->height != 1 && (second->height != first->height || second->width != first->width)) || 
        (second->height == 1 && second->width != first->height)) {
        return NULL;
    }

    array* arr = zero_array(first->height, first->width);

    if (second->height == 1) {
        #pragma omp parallel for
        for (int i = 0; i < second->width; i++) {
            for (int j = 0; j < first->width; j++) {
                arr->values[i][j] = f(first->values[i][j], second->values[0][i]);
            }
        }
    } else {
        #pragma omp parallel for
        for (int i = 0; i < first->height; i++) {
            for (int j = 0; j < first->width; j++) {
                arr->values[i][j] = f(first->values[i][j], second->values[i][j]);
            }
        }
    }

    return arr;
}

array* array_agg_self(array const* first, double (*f)(double)) {
    array* arr = zero_array(first->height, first->width);

    #pragma omp parallel for
    for (int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            arr->values[i][j] = f(first->values[i][j]);
        }
    }

    return arr;
}

array* array_agg_rvalue(array const* first, double second, double (*f)(double, double)) {
    array* arr = zero_array(first->height, first->width);

    #pragma omp parallel for
    for (int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            arr->values[i][j] = f(first->values[i][j], second);
        }
    }

    return arr;
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

array* array_sub(array const* first, array const* second) {
    return array_agg_other(first, second, sub);
}

array* array_add(array const* first, array const* second) {
    return array_agg_other(first, second, add);
}

array* array_mul(array const* first, array const* second) {
    return array_agg_other(first, second, mul);
}

array* array_div(array const* first, array const* second) {
    return array_agg_other(first, second, divide);
}

array* array_pow(array const* first, array const* second) {
    return array_agg_other(first, second, power);
}

array* array_pow_single(array const* first, double second) {
    return array_agg_rvalue(first, second, power);
}

array* array_sub_single(array const* first, double second) {
    return array_agg_rvalue(first, second, sub);
}

array* array_add_single(array const* first, double second) {
    return array_agg_rvalue(first, second, add);
}

array* array_mul_single(array const* first, double second) {
    return array_agg_rvalue(first, second, mul);
}

array* array_div_single(array const* first, double second) {
    return array_agg_rvalue(first, second, divide);
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

array* array_sqrt(array const* first) {
    return array_agg_self(first, square_root);
}

array* array_exp(array const* first) {
    return array_agg_self(first, exponent);
}

array* array_log(array const* first) {
    return array_agg_self(first, logarithm);
}

array* array_part(array const* first, uint32_t start, uint32_t end, uint8_t dim) {
    array* arr;
    
    if (start > end || dim < 0 || first == NULL || start < 0 || end < 0) {
        return NULL;
    } else if (dim == 0) {
        arr = zero_array(end - start, first->width);

        #pragma omp parallel for
        for (int i = start; i < end; i++) {
            for (int j = 0; j < first->width; j++) {
                arr->values[i][j] = first->values[i][j];
            }
        }
    } else if (dim == 1) {
        arr = zero_array(first->height, end - start);
        
        #pragma omp parallel for
        for (int i = 0; i < first->height; i++) {
            for (int j = start; j < end; j++) {
                arr->values[i][j] = first->values[i][j];
            }
        }
    }
    return arr;
}

array* array_argmax(array const* first, uint8_t dim) {
    array* arr = NULL;

    if (dim == 0) {
        arr = zero_array(1, first->height);

        #pragma omp parallel for
        for (int i = 0; i < first->height; i++) {
            double max_value = 0;
            uint32_t max_index = 0;
            for (int j = 0; j < first->width; j++) {
                if (first->values[i][j] > max_value) {
                    max_index = j;
                    max_value = first->values[i][j];
                }
            }

            arr->values[0][i] = (double)max_index;
        }
    } else if (dim == 1) {
        arr = zero_array(1, first->height);

        #pragma omp parallel for
        for (int i = 0; i < first->width; i++) {
            double max_value = 0;
            uint32_t max_index = 0;
            for (int j = 0; j < first->height; j++) {
                if (first->values[i][j] > max_value) {
                    max_index = j;
                    max_value = first->values[i][j];
                }
            }

            arr->values[0][i] = (double)max_index;
        }
    }

    return arr;
}

array* array_transpose(array const* first) {
    array* arr = zero_array(first->width, first->height);

    #pragma omp parallel for
    for (int i = 0; i < first->width; i++) {
        for (int j = 0; j < first->height; j++) {
            arr->values[i][j] = first->values[i][j];
        }
    }

    return arr;
}

array* range_array(uint32_t number) {
    array* arr = zero_array(1, number);

    #pragma omp parallel for
    for (int i = 0; i < number; i++) {
        arr->values[0][i] = i;
    }

    return arr;
}

array* array_at(array const* first, array const* second, uint8_t dim) {
    if (second->height != 1) {
        return NULL;
    }

    array* arr = zero_array(1, second->width);

    if (dim == 0) {

        #pragma omp parallel for
        for (int i = 0; i < second->width; i++) {
            arr->values[i][0] = first->values[(uint64_t)second->values[0][i]][0];
        }
    } else if (dim == 1) {

        #pragma omp parallel for
        for (int i = 0; i < second->height; i++) {
            arr->values[i][0] = first->values[0][(uint64_t)second->values[0][i]];
        }
    }

    return arr;
}

array* array_maximum(array const* first, double number) {
    array* arr = zero_array(first->height, first->width);

    #pragma omp parallel for
    for(int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            arr->values[i][j] = first->values[i][j] > number ? first->values[i][j] : number; 
        }
    }

    return arr;
}

void array_set(array const* first, array const* second, double value) {
    if (second->height != 1) {
        
        #pragma omp parallel for
        for (int i = 0; i < second->height; i++) {
            double* index = second->values[i];
            for (int j = 0; j < second->width; j++) {
                first->values[(uint64_t)index[0]][(uint64_t)index[j]] = value;
            }
        }
    } else if (second->height == 1) {
        
        #pragma omp parallel for
        for (int i = 0; i < second->width; i++) {
            for (int j = 0; j < first->height; j++) {
                first->values[j][(uint64_t)second->values[0][i]] = value;
            }
        }
    }
}

double array_sum(array const* first) {
    double sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < first->height; i++) {
        for (int j = 0; j < first->width; j++) {
            sum += first->values[i][j];
        }
    }

    return sum;
}
