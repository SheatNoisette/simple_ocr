/*
** image_tools.c for OCR in src/bitmap
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

//Imports
#include <stddef.h>

#include "image.h"

//------------------------------
// Functions

image *crop_image_at (
    image *img, unsigned int x1, unsigned int y1, 
    unsigned int x2, unsigned int y2
);

image *image_resize_linear_interp 
(image *img, unsigned int new_width, unsigned int new_height);

matrix *image_to_binmatrix(image *input);

void image_to_binmatrix_fill(matrix *matrix_in, image *input_image);

#endif