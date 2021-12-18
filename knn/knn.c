/*
@author Yanir Harel
*/

#include "knn.h"

void swap(uint16_t* a, uint16_t* b) 
{ 
    uint16_t t = *a; 
    *a = *b; 
    *b = t; 
} 
  
int partition (double values[], uint16_t arr[], int low, int high) 
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
  
void quickSort(double values[], uint16_t arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(values, arr, low, high); 
  
        quickSort(values, arr, low, pi - 1); 
        quickSort(values, arr, pi + 1, high);
    } 
} 

double** knn_fit_predict(double* element, double** neighbors, uint16_t height, uint16_t width, uint16_t k) {
    if (k > height) {
        return NULL;
    }

    double* nearest_neighbors_distances = malloc(height * sizeof(double));
    uint16_t* nearest_neighbors_indexes = malloc(height * sizeof(uint16_t));
    double** k_nearest_neighbors = malloc(k * sizeof(double*));
    
    #pragma omp parallel

    for (int i = 0; i < height; i++) {
        double l2_distance = 0;
        for (int j = 0; j < width; j++) {
            l2_distance += pow(element[j] - neighbors[i][j], 2);
        }

        l2_distance = sqrt(l2_distance);
        nearest_neighbors_distances[i] = l2_distance;
        nearest_neighbors_indexes[i] = i;
    }
    
    quickSort(nearest_neighbors_distances, nearest_neighbors_indexes, 0, height - 1);

    for (int neighbor = 0; neighbor < k; neighbor++) {
        k_nearest_neighbors[neighbor] = neighbors[nearest_neighbors_indexes[neighbor]];
    }

    free(nearest_neighbors_distances);
    free(nearest_neighbors_indexes);

    return k_nearest_neighbors;
}