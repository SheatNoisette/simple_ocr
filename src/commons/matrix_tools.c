/*
** matrix_tools.h for OCR in src/commons
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

/*
** Prettyprint the matrix
*/
void pretty_print_matrix(matrix *input) {

    /* Iterators */
    unsigned int x;
    unsigned int y;

    /* Matrix size */
    unsigned int matrix_height;
    unsigned int matrix_width;

    /* Check the matrix */
    if (input == NULL) {
        printf("[Matrix] Matrix print: Invalid matrix\n");
        return;
    }

    /* Get size of the matrix */
    matrix_height = input->height;
    matrix_width = input->width;

    for (y = 0; y < matrix_height; y++) {
        for (x = 0; x < matrix_width; x++) {
            printf("%d ", get_value_matrix(input, x, y));
        }

        printf("\n");
    }
}

/*
** Convert matrix to float array
*/

float *matrix_to_float_array(matrix *input) {

    /* Float array exported */
    float *array;

    /* Matrix size */
    unsigned int matrix_height;
    unsigned int matrix_width;

    /* Iterators */
    unsigned int y;
    unsigned int x;

    /* Set size from matrix input */
    matrix_height = input->height;
    matrix_width = input->width;

    /* Create the array */
    array = malloc(sizeof(float) * matrix_height * matrix_width);

    /* Iterate to fill the array */
    for (y = 0; y < matrix_height; y++) {
        for (x = 0; x < matrix_width; x++) {
            array[x + matrix_width * y] = (float) get_value_matrix(input, x, y);
        }
    }
    
    return array;
}