/*
** binarization.c for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../bitmap/image.h"
#include "../commons/matrix.h"

/*
** Simple threshold binarization algorithm
*/

void i_binarization_threshold(image *input, unsigned char threshold) {

    unsigned char red_pixel;
    unsigned char color;
    unsigned int y;
    unsigned int x;

    for (y = 0; y < input->height; y++) {
        for (x = 0; x < input->width; x++){

            red_pixel = get_pixel(input, C_RED, x, y);

            color = red_pixel;

            /* Dead simple thresholding binarization method */
            if (color > threshold) {
                    color = 255;

            } else {
                color = 0;
            }

            /* Set every pixel like this */
            set_pixel(input, x, y, color, color, color);
        }
    }

}

/*
** Otsu's binarization method
*/

void i_otsu_method_binarization (image *input) {

    /* Create histogram */
    unsigned char histogram[256];
    memset(histogram, 0, 255);

    /* Weights */
    int background_weight = 0;
    int foreground_weight = 0;

    /* Image size */
    unsigned long image_size = input->width * input->height;

    /* Background number of pixel */
    float background_sum = 0;

    /* Mean blackground and foreground */
    float mean_back = 0;
    float mean_fore = 0;

    /* Histogram sum */
    double histogram_sum = 0;

    /* Class variance */
    double variance = 0;

    /* Maximum variance */
    double max_variance = 0;

    /*  Our threshold */
    unsigned char threshold = 0;

    /* Iterators */
    unsigned int x;
    unsigned int y;
    unsigned int cursor;

    /* Threshold level */
    unsigned long level;

    for (y = 0; y < input->height; y++) {
        for (x = 0; x < input->width; x++){
            /* Add entry to histogram */
            histogram[input->pixel[x + y*input->width].red] += 1;
        }
    }

    /* Compute histogram sum for mean values */
    for (cursor = 0; cursor < 256; cursor ++) {
        histogram_sum += cursor * histogram[cursor];
    }

    /* Find threshold */
    for (level = 0; level < 256; level++) {

        /* Compute background weight */
        background_weight  += histogram[level];

        /* Compute foreground weight */
        foreground_weight  += image_size - background_weight;

        /* Check if we can't split foreground and background anymore */
        if (foreground_weight != 0) {

            background_sum += (float)level * histogram[level];

            mean_back = background_sum / background_weight;

            mean_fore = (image_size - background_sum ) / mean_fore;

            /* Compute variance */
            variance = background_weight * foreground_weight *
                        pow((mean_back - mean_fore), 2);

            /* Check if we found a new maximum */
            if (max_variance < variance) {
                /*  Found threshold! */
                threshold = level;
                max_variance = variance;
            }

        }
    }

    /* Apply binarization with our mightly new threshold! */
    i_binarization_threshold(input, threshold);
}
