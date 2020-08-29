/*
** matrix.h for OCR in src/commons
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef MATRIX_H
#define MATRIX_H

/* ---------------------------------- */
/*  Structures */

typedef struct
{
    int width;
    int height;

    int *content;
} matrix;

/* ---------------------------------- */
/*  Virtual functions */

matrix* create_matrix (unsigned int width, unsigned int height);

void free_matrix (matrix* selected_matrix);

int get_value_matrix (matrix* i_matrix, unsigned int x, unsigned int y);

void set_value_matrix 
(matrix* i_matrix, unsigned int x, unsigned int y, int value);

#endif