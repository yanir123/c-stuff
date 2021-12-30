/*
@author Yanir Harel
*/

#include "knn.h"

double** knn_fit_predict(double* element, double** neighbors, uint32_t height, uint32_t width, uint16_t k) {
    if (k > height) {
        return NULL;
    }

    double* nearest_neighbors_distances = malloc(height * sizeof(double));
    uint32_t* nearest_neighbors_indexes = malloc(height * sizeof(uint32_t));
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