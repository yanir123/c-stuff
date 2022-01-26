#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>

struct array {
    uint32_t height;
    uint32_t width;
    double** values;
} typedef array;

array* dot_product(array const* first, array const* second);
void quickSort(double values[], uint32_t arr[], int low, int high);
int partition (double values[], uint32_t arr[], int low, int high);
void swap(uint32_t* a, uint32_t* b);
void free_array(array* arr);
array* random_array(uint32_t height, uint32_t width, double max_rand, double min_rand);
array* zero_array(uint32_t height, uint32_t width);
double random_double(double max, double min);
array* array_agg_other(array const* first, array const* second, double (*f)(double, double));
array* array_agg_self(array const* first, double (*f)(double));
array* array_agg_rvalue(array const* first, double second, double (*f)(double, double));
double sub(double first, double second);
double add(double first, double second);
double mul(double first, double second);
double divide(double first, double second);
double power(double first, double second);
double square_root(double first);
double exponent(double first);
double logarithm(double first);
array* array_sub(array const* first, array const* second);
array* array_add(array const* first, array const* second);
array* array_mul(array const* first, array const* second);
array* array_div(array const* first, array const* second);
array* array_pow(array const* first, array const* second);
array* array_sqrt(array const* first);
array* array_exp(array const* first);
array* array_log(array const* first);
array* array_sub_single(array const* first, double second);
array* array_add_single(array const* first, double second);
array* array_mul_single(array const* first, double second);
array* array_div_single(array const* first, double second);
array* array_pow_single(array const* first, double second);
void array_print(array* arr);