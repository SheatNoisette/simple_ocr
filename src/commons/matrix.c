/*
** matrix.c for OCR in src/commons
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
** Create a simple matrix
*/

matrix* create_matrix (unsigned int width, unsigned int height) {

    /* Create a basic pointer for the struct */
    matrix *new_array = malloc(sizeof(matrix));

    /* Check malloc */
    if (new_array == NULL) {
        printf("[Matrix] Failed to create a matrix");
        return NULL;
    }

    /* Set some properties */
    new_array->width = (unsigned int)width;
    new_array->height = (unsigned int)height;
    new_array->content = malloc(width * height * sizeof(int));

    /* Check if the memory alloc was successful */
    if (new_array->content == NULL) {
        printf("[Matrix] Failed to allocate matrix content");
        return NULL;
    }

    return new_array;
}

/*
** Delete matrix
*/

void free_matrix (matrix *selected_matrix) {

    /* Check if matrix exists */
    if (selected_matrix == NULL) {
        printf("[Matrix] Trying to released a invalid matrix\n");
        return;
    }

    free(selected_matrix->content);
    free(selected_matrix);
}

/*
** Get value from matrix at x, y
*/

int get_value_matrix (matrix *i_matrix, unsigned int x, unsigned int y) {

    unsigned int matrix_position = x + i_matrix->width * y;

    return i_matrix->content[matrix_position];
}

/*
** Set value from matrix at x, y
*/

void set_value_matrix 
(matrix *i_matrix, unsigned int x, int unsigned y, int value) {

    unsigned int matrix_position = x + i_matrix->width * y;

    /* Set value */
    i_matrix->content[matrix_position] = value;
}
