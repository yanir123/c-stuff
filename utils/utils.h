#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

struct array {
    uint32_t height;
    uint32_t width;
    double** values;
} typedef array;

array* dot_product(array first, array second);
void quickSort(double values[], uint32_t arr[], int low, int high);
int partition (double values[], uint32_t arr[], int low, int high);
void swap(uint32_t* a, uint32_t* b);