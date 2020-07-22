/*
** convolution_matrix.h for OCR in src/filters
**
** Made by jpbinger
** Login   jpbinger
**
** Started on  2019 jpbinger
*/

#include "../bitmap/image.h"
#include "../commons/matrix.h"

#ifndef CONVOLUTION_MATRIX_H
#define CONVOLUTION_MATRIX_H

matrix* create_pixel_matrix(image* input, int x, int y, int width);
int convolution_matrix_multiply(matrix* pixels, matrix* convolution_mask, int active);
image* extend_border(image* input, int width);
image* convolution_matrix_filter(image* input, matrix* convolution_mask,int active);
#endif
