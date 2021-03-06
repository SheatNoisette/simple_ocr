#include <stdio.h>
#include <stdlib.h>

#include "../bitmap/image.h"
#include "../commons/utils.h"

void i_grayscale_lightness(image *input)
{
    unsigned char red_pixel;
    unsigned char green_pixel;
    unsigned char blue_pixel;
    unsigned char average;

    for (unsigned int x = 0; x < input->width; x++)
    {
        for (unsigned int y = 0; y < input->height; y++)
        {
            red_pixel = get_pixel(input, C_RED, x, y);
            green_pixel = get_pixel(input, C_GREEN, x, y);
            blue_pixel = get_pixel(input, C_BLUE, x, y);

            average = (max_3(red_pixel, green_pixel, blue_pixel)
                       + min_3(red_pixel, blue_pixel, green_pixel))
                / 2;

            set_pixel(input, x, y, average, average, average);
        }
    }
}
