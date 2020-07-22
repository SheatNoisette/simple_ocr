/*
** binarization.h for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef BINARIZATION_H
#define BINARIZATION_H

#include "../bitmap/image.h"

//---------------------------
// Functions

void i_binarization_threshold(image *input, unsigned char threshold);
void i_otsu_method_binarization(image *input);
#endif
