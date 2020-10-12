/*
** convolution_matrix.c for OCR in src/filters
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
/*
 *   Create a matrix with the pixel value of the grayscale image
 */
matrix *create_pixel_matrix(image *input, unsigned int x, unsigned int y,
                            int width)
{
    // create a square matrix of order width
    matrix *output = create_matrix(width, width);
    for (unsigned int i = x - width / 2; i <= x + width / 2; i++)
    {
        for (unsigned int j = y - width / 2; j <= y + width / 2; j++)
        {
            set_value_matrix(output, x + width / 2 - i, y + width / 2 - j,
                             get_pixel(input, C_RED, i, j));

            // printf("%i  %i\n",j,get_pixel(input,C_RED,i,j) );
        }
    }
    return output;
}

/*
 *   apply the summerization of the multiplication of the value of each
 *   value from both matrix
 */
int convolution_matrix_multiply(matrix *pixels, matrix *convolution_mask,
                                int active)
{
    int result = 0;
    for (int i = 0; i < pixels->width; i++)
    {
        for (int j = 0; j < pixels->height; j++)
        {
            result += get_value_matrix(pixels, i, j)
                * get_value_matrix(convolution_mask, i, j);

            // printf("%i\n",get_value_matrix(pixels,i,j) );
        }
    }
    result = result / active;
    if (result < 0)
    {
        return 0;
    }
    if (result >= 256)
    {
        return 255;
    }
    return result;
}

/*
 *   Replace the border that havn't been changed by the convolution method
 *   by the nearest pixel that have been changed
 */
image *extend_border(image *input, unsigned int width)
{
    for (unsigned int i = width / 2; i < input->width; i++)
    {
        // calculate the upper border pixel color
        int red_up = get_pixel(input, C_RED, i, width / 2);
        int green_up = get_pixel(input, C_GREEN, i, width / 2);
        int blue_up = get_pixel(input, C_BLUE, i, width / 2);

        // calculate the lower border pixel color
        int red_low =
            get_pixel(input, C_RED, i, input->height - 1 - (width / 2));
        int green_low =
            get_pixel(input, C_GREEN, i, input->height - 1 - (width / 2));
        int blue_low =
            get_pixel(input, C_BLUE, i, input->height - 1 - (width / 2));

        // set the color on the border height
        for (unsigned int j = 0; j < width / 2; j++)
        {
            // replace the upper border without external border
            set_pixel(input, i, j, red_up, green_up, blue_up);

            // replace the lower border without external border
            set_pixel(input, i, input->height - 1 - j, red_low, green_low,
                      blue_low);
        }
    }
    for (unsigned int i = 0; i < input->height; i++)
    {
        // calculate the left border pixel color
        int red_left = get_pixel(input, C_RED, width / 2, i);
        int green_left = get_pixel(input, C_GREEN, width / 2, i);
        int blue_left = get_pixel(input, C_BLUE, width / 2, i);

        // calculate the right border pixel color
        int red_right =
            get_pixel(input, C_RED, input->width - 1 - (width / 2), i);
        int green_right =
            get_pixel(input, C_GREEN, input->width - 1 - (width / 2), i);
        int blue_right =
            get_pixel(input, C_BLUE, input->width - 1 - (width / 2), i);

        // set the color on the border height
        for (unsigned int j = 0; j < width / 2; j++)
        {
            // replace the upper border without external border
            set_pixel(input, j, i, red_left, green_left, blue_left);

            // replace the lower border without external border
            set_pixel(input, input->height - 1 - j, i, red_right, green_right,
                      blue_right);
        }
    }
    return input;
}

/*
 *   Copy an image of a certain dimension in a destination of the same dimension
 */
void Copy_image(image *dst, image *src)
{
    for (unsigned int i = 0; i < src->width; i++)
    {
        for (unsigned int j = 0; j < src->height; j++)
        {
            set_pixel(dst, i, j, get_pixel(src, C_RED, i, j),
                      get_pixel(src, C_GREEN, i, j),
                      get_pixel(src, C_BLUE, i, j));
        }
    }
}

/*
 *   Apply the convolution mehtod with the convolution_mask matrix
 */
image *convolution_matrix_filter(image *input, matrix *convolution_mask,
                                 int active)
{
    // create a copy of the image
    image *output = create_image(input->width, input->height);
    Copy_image(output, input);

    // replace the inner of the new image
    for (unsigned int i = convolution_mask->width / 2;
         i < input->width - 1 - convolution_mask->width / 2; i++)
    {
        for (unsigned int j = convolution_mask->width / 2;
             j < input->height - 1 - convolution_mask->width / 2; j++)
        {
            int new_pixel = convolution_matrix_multiply(

                create_pixel_matrix(input, i, j, convolution_mask->width),

                convolution_mask, active);

            set_pixel(output, i, j, new_pixel, new_pixel, new_pixel);
        }
    }

    free_image(input);
    // replace the border of the image
    extend_border(output, convolution_mask->width);
    return output;
}
