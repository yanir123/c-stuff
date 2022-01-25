#include "svm.h"

int main(int argc, char** argv, char** env) {
    srand(time(NULL));

    array* first = random_array(4, 2, 5.0, -4.0);
    // array* second = random_array(1, 4, 5.0, -4.0);

    array_print(first);
    // array_print(second);

    array_exp(first);

    array_print(first);

    free_array(first);
    // free_array(second);

    return 0;
}