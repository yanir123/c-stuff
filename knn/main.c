/*
@author Yanir Harel
*/

#include "knn.h"
#include <stdio.h>
#include <time.h>

#define K 3
#define HEIGHT 3
#define WIDTH 3

int main(int argc, char** argv, char** env) {
    double element[WIDTH] = {1, 2, 3, 4, 5};

    double** neighbors = malloc(sizeof(double*) * HEIGHT);
    
    for (int i = 0; i < HEIGHT; i++) {
        neighbors[i] = malloc(sizeof(double) * WIDTH);
        for (int j = 0; j < WIDTH; j++) {
            neighbors[i][j] = (rand() % (100 - 0 + 1)) + 0;
        }
    }

    time_t start = time(NULL);
    double** k_nearest_neighbors = knn_fit_predict(element, neighbors, WIDTH, HEIGHT, K);
    time_t end = time(NULL);

    for (int neighbor = 0; neighbor < K; neighbor++) {
        printf_s("{ ");
        for (int field = 0; field < WIDTH; field++) {
            printf_s("%f ", k_nearest_neighbors[neighbor][field]);
        }
        printf_s("}\n");
    }

    printf_s("Execution time is: %f\n", (end - start));

    for (int i = 0; i < HEIGHT; i++) {
        free(neighbors[i]);
    }

    free(k_nearest_neighbors);
    free(neighbors);

    return 0;
}