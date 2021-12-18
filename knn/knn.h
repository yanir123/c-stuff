/*
@author Yanir Harel
*/

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

/*
Function to get the k neighbors with the smallest distances.
    @param element double* - the base elements to check the distances from (size of (width))
    @param neighbors double** - the neigbors to compare the element to (size of (height, width))
    @param height uint16_t - the number of elements to compare to base
    @param width uint16_t - the number of fields that compose the elements
    @param k uint16_t - the number of nearest neighbors
    @return array of size k of the closest neighbors (size of (k, width))(needs to be free)

*/
double** knn_fit_predict(double* element, double** neighbors, uint16_t height, uint16_t width, uint16_t k);
void quickSort(double values[], uint16_t arr[], int low, int high);
int partition (double values[], uint16_t arr[], int low, int high);
void swap(uint16_t* a, uint16_t* b);