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
