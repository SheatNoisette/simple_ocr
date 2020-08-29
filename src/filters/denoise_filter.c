/*
** denoise_filter.c for OCR in src/filters
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
*   Apply a denoise filter
*/
image* denoise_filter(image* input)
{
    /* Output image */
    image* output = NULL;

    /* Iterators */
    int i;
    int j;

    /* Main convolution mask */
    matrix* convolution_mask = create_matrix(3,3);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            set_value_matrix(convolution_mask,i,j,1);
        }
    }
    output = convolution_matrix_filter(input,convolution_mask,9);
    free_image(input);
    return output;
}
