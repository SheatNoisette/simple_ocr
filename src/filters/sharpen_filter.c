/*
** sharpen_filter.c for OCR in src/filters
**
** Made by jpbinger
** Login   jpbinger
**
** Started on  2019 jpbinger
*/

#include <stdio.h>
#include <stdlib.h>

#include "../bitmap/image.h"
#include "../commons/matrix.h"
#include "convolution_matrix.h"
#include "binarization.h"

/*
*   Apply a sharpen_filter filter
*/
image* sharpen_filter(image* input)
{
    //create a matrix with 0 in the corner
    matrix* convolution_mask = create_matrix(3,3);
    for (int i = 0; i < 3; i+= 2) {
        for (int j = 0; j < 3; j+= 2) {
            set_value_matrix(convolution_mask,i,j,0);
        }
    }

    //apply -1 on the middle of every border and 5 in the center of the matrix
    set_value_matrix(convolution_mask,1,0,-1);
    set_value_matrix(convolution_mask,0,2,-1);
    set_value_matrix(convolution_mask,0,1,-1);
    set_value_matrix(convolution_mask,1,2,-1);
    set_value_matrix(convolution_mask,1,1,5);
    image* output = convolution_matrix_filter(input,convolution_mask,1);
    free_image(input);
    return output;
}
