/*
** basic_filters.c for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdio.h>
#include <stdlib.h>

#include "../bitmap/image.h"

/*
** Grayscale image
** Simple image grayscale using average
*/

void i_grayscale_average(image *input)
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

            average = (red_pixel + blue_pixel + green_pixel) / 3;

            set_pixel(input, x, y, average, average, average);
        }
    }
}

/*
** Grayscale image
** Simple image grayscale using luminosity offset
*/

void i_grayscale_luminosity(image *input)
{
    unsigned char red_pixel;
    unsigned char green_pixel;
    unsigned char blue_pixel;

    unsigned char color;

    for (unsigned int x = 0; x < input->width; x++)
    {
        for (unsigned int y = 0; y < input->height; y++)
        {
            red_pixel = get_pixel(input, C_RED, x, y);
            green_pixel = get_pixel(input, C_GREEN, x, y);
            blue_pixel = get_pixel(input, C_BLUE, x, y);

            color = 0.21 * red_pixel + 0.72 * blue_pixel + 0.07 * green_pixel;

            // Set every pixel like this
            set_pixel(input, x, y, color, color, color);
        }
    }
}