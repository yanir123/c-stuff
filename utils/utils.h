#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>

/*
    Struct that represents a 2D array
*/
struct array {
    uint32_t height;
    uint32_t width;
    double** values;
} typedef array;

/*
    Function that performs a dot product on two arrays (arrays dimensions must be transposed)
    @param first array const* - 2D array to be the left operand of the dot product
    @param second array const* - 2D array to be the right operand of the dot product
    @return A new array that is the dot product of the two arrays (don't forget to free)
*/
array* dot_product(array const* first, array const* second);

/*
    Function that implements a quicksort
    @param values double[] - Array to be sorted
    @param arr uint32_t[] - Index array
    @param low int - bottom index
    @param high int - top index
    @return None
*/
void quickSort(double values[], uint32_t arr[], int low, int high);

/*
    Function to partition an array
    @param values double[] - Array to be sorted
    @param arr uint32_t[] - Index array
    @param low int - bottom index
    @param high int - top index
    @return New index to sort from
*/
int partition (double values[], uint32_t arr[], int low, int high);



/*
    Function to swap the values of two numbers
    @param a uint32_t* - first number
    @param b uint32_t* - second number
    @return None
*/
void swap(uint32_t* a, uint32_t* b);

/*
    Function to free an 'array' struct
    @param arr array* - array to free
    @return None
*/
void free_array(array* arr);

/*
    Function to create array of specific size filled with random numbers in it
    @param height uint32_t - size of the first dimension
    @param width uint32_t - size of the second dimension
    @param max_rand double - biggest number in random range
    @param min_rand double - smallest number in random range
    @return A new array of size (height, width) filled with random numbers from min_rand to max_rand
*/
array* random_array(uint32_t height, uint32_t width, double max_rand, double min_rand);

/*
    Function to create array of specific size filled with zeros
    @param height uint32_t - size of the first dimension
    @param width uint32_t - size of the second dimension
    @return A new array filleed with zeros of size (height, width)
*/
array* zero_array(uint32_t height, uint32_t width);

/*
    Function to create array of specific size with values equal to their index
    @param number uint32_t - size of the array (max value in range + 1)
    @return A new array fileed with values equal to their index of size (1, number) 
*/
array* range_array(uint32_t number);

/*
    Function to manifest a random decimal number
    @param max double - biggest number in random range
    @param min double - smallest number in random range
    @return A random decimal number between min and max
*/
double random_double(double max, double min);

/*
    Function to run over the elemnts of the first array and perform a function with second array
    @param first array const* - array to aggregate over
    @param second array const* - array to aggregate with
    @param f double (*)(double, double) - the aggregation function
    @return A new array with the aggregation result
*/
array* array_agg_other(array const* first, array const* second, double (*f)(double, double));

/*
    Function to run over the elements of the first array and perform a function on it
    @param first array const* - array to aggregate over
    @param f double (*)(double) - the aggregation function
    @return A new array with the aggregation result
*/
array* array_agg_self(array const* first, double (*f)(double));

/*
    Function to run over the elements of the first array and perform a function with number
    @param first array const* - array to aggregate over
    @param second double - value to aggregate with
    @param f double (*)(double, double)
    @return A new array with the aggregation result
*/
array* array_agg_rvalue(array const* first, double second, double (*f)(double, double));

/*
    Function to subtract one number from another
    @param first double - minuend
    @param second double - subtrahend
    @return the difference of the two numbers
*/
double sub(double first, double second);

/*
    Function to add two numbers
    @param first double - augend
    @param second double - addend
    @return the sum of the two numbers
*/
double add(double first, double second);

/*
    Function to multiply two numbers
    @param first double - multiplier
    @param second double - multiplicand
    @return the product of the two numbers
*/
double mul(double first, double second);

/*
    Function to divide one number from another
    @param first double - dividend
    @param second double - divisor
    @return the fraction of the two numbers
*/
double divide(double first, double second);

/*
    Function to perform exponentiation
    @param first double - base
    @param second double - exponent
    @return the first number at the power of the second
*/
double power(double first, double second);

/*
    Function to perform square root of a number
    @param first double - radicand
    @return the 2nd degree root of the number
*/
double square_root(double first);

/*
    Function to perform e at the power of a number
    @param first double - exponent
    @return e at the power of first
*/
double exponent(double first);

/*
    Functioin to perform log of a number
    @param first double - anti-logarithm
    @return logarithm of first
*/
double logarithm(double first);

/*
    Function to subtract one array from another
    @param first array const* - minuend
    @param second array const* - subtrahend
    @return A new array containing the differance of the arrays
*/
array* array_sub(array const* first, array const* second);

/*
    Function to add two arrays
    @param first array const* - augend
    @param second array const* - addend
    @return A new array containing the sum of the arrays
*/
array* array_add(array const* first, array const* second);

/*
    Function to multiply two arrays
    @param first array const* - multiplier
    @param second array const* - multiplicand
    @return A new array containing the product of the two arrays
*/
array* array_mul(array const* first, array const* second);

/*
    Function to divide one array from another
    @param first array const* - dividend
    @param second array const* - divisor
    @return A new array containing the fraction of the two arrays
*/
array* array_div(array const* first, array const* second);

/*
    Function to perform exponantiation of two arrays
    @param first array const* - base
    @param second array const* - exponent
    @return A new array containing the exponention of the two arrays
*/
array* array_pow(array const* first, array const* second);

/*
    Function to perform square root of an array
    @param first double const* - radicand
    @return A new array containing the square root of the array
*/
array* array_sqrt(array const* first);

/*
    Function to perform e at the power of array
    @param first array const* - exponent
    @return A new array containing e at the power of the values in the first array
*/
array* array_exp(array const* first);

/*
    Function to perform logarith on the values of an array
    @param first array const* - anti-logarithm
    @return A new array with the logarithm of the first array
*/
array* array_log(array const* first);

/*
    Function to subtract a number from all values of the array
    @param first array const* - minuend
    @param second double - subtrahend
    @return A new array with containing the difference of the array and the number
*/
array* array_sub_single(array const* first, double second);

/*
    Function to add a number to all values of an array
    @param first array const* - augend
    @param second double - addend
    @return A new array containing the sum of the array and the number
*/
array* array_add_single(array const* first, double second);

/*
    Function to multiply all values of the array by number
    @param first array const* - multiplier
    @param second double - multiplicand
    @return A new array containing the sum of the number and the array
*/
array* array_mul_single(array const* first, double second);

/*
    Function to divide all values of the array by number
    @param first array const* - dividend
    @param second double - divisor
    @return A new array containing the fraction the the array by number
*/
array* array_div_single(array const* first, double second);

/*
    Function to perform exponention of the array by number
    @param first array const* - base
    @param second double - exponent
    @return A new array containing the power of the array by number
*/
array* array_pow_single(array const* first, double second);

/*
    Function to extract a part of an array
    @param first array const* - array to partition
    @param start uint32_t - index to the start of the partition
    @param end uint32_t - index to the end of the partition
    @param dim uint8_t - indecation of the partition orientation - vertical/horizontal (0/1)
    @return A new array containing the partition
*/
array* array_part(array const* first, uint32_t start, uint32_t end, uint8_t dim);

/*
    Function to find the index of the maximum value in given array
    @param first array const* - array to find max in
    @param dim uint8_t - indecation of the max search orientation - vertical/horizontal (0/1)
    @return A new array containing the indexes of the maximum values
*/
array* array_argmax(array const* first, uint8_t dim);

/*
    Function to print an array
    @param arr array* - array to print
    @return None
*/
void array_print(array* arr);

/*
    Function to transpose an array ie. rotate the shape
    @param first array const* - array to transpose
    @return A new array representing the transposed array
*/
array* array_transpose(array const* first);

/*
    Function to select an index from the array
    @param first array const* - array to select from
    @param second array const* - array containing the indexes
    @param dim uint8_t - indecation of the selection orientation - vertical/horizontal (0/1)
    @return A new array containing the selected values
*/
array* array_at(array const* first, array const* second, uint8_t dim);

/*
    Function to aggregate maximum ie. max(value, number) on the array
    @param first array const* - array to aggregate over
    @param number double - operand for the max function
    @return A new array containing the aggregation result
*/
array* array_maximum(array const* first, double number);

/*
    Function to set values in given array
    @param first array const* - array to set values at
    @param second array const* - array conotaining indexes to put at
    @param value double - value to set at indexes
    @return 1 if success 0 if failure
*/
void array_set(array const* first, array const* second, double value);

/*
    Function to sum all the values of an array
    @param first array const* - array to sum
    @return the sum of all the values in the array
*/
double array_sum(array const* first);