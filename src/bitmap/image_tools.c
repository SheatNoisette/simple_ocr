/*
** image_tools.c for OCR in src/bitmap
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdio.h>
#include <math.h>

#include "image.h"
#include "../commons/utils.h"
#include "../commons/matrix.h"

/* Image manipulation */

/* Extract image from image at x1,y1 and x2,y2 */
image *crop_image_at (
    image *img, unsigned int x1, unsigned int y1, 
    unsigned int x2, unsigned int y2
) {
    /* Color channel */
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    /* Loop iterator */
    unsigned int x;
    unsigned int y;

    /* Get original image size */
    unsigned int image_width = (unsigned int) img->width;
    unsigned int image_height = (unsigned int) img->height;

    /* Check if the coordinates are valid */
    if (y1 >= y2 || x1 >= x2 || y2 > image_height || x2 > image_width) {
        printf("[Image] Can't crop image, invalid coordinates\n");
        printf("[Image] Got x1: %i y1: %i x2: %i y2: %i\n", x1, y1, x2, y2);
        printf("[Image] Max size is: h: %u w: %u\n", image_width, image_height);
        return NULL;
    }

    /* Do the cropping */
    /* Create image */
    /* printf("%u %u %u %u %u %u\n", x1, y1, x2, y2, x2 - x1, y2 - y1); */
    image *cropped_img = create_image(x2 - x1, y2 - y1);

    for (y = y1; y < y2; y++)
    {
        for (x = x1; x < x2; x++)
        {
            red = get_pixel_safe(img, C_RED, x, y);
            green = get_pixel_safe(img, C_GREEN, x, y);
            blue = get_pixel_safe(img, C_BLUE, x, y);
            set_pixel_safe(cropped_img, x - x1, y - y1, red, green, blue);
        }
    }
    
    return cropped_img;
}

/*  Linear Interpolation resizing */
/*  Resize image using Linear Interpolation */

image *image_resize_linear_interp 
(image *img, unsigned int new_width, unsigned int new_height) {

    /* Loop iterators */
    unsigned int x;
    unsigned int y;

    /* Color channels */
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    /* New coordinates for input image (pixel reference) */
    unsigned int new_x; 
    unsigned int new_y; 

    /* Check if the image exists */
    if (img == NULL) {
        printf("[Image] Linear Interpolation: Image pointer is null!\n");
        return NULL;
    }

    /* Create our new image */
    image *resized_img = create_image(new_width, new_height);

    /* Get image size property */
    unsigned int image_width = img->width;
    unsigned int image_height = img->height;

    /* Apply the algorithm */
    for (y = 0; y < new_height; y++)
    {
        for (x = 0; x < new_width; x++) {

            new_x = (int)
                    roundf((float)x / (float)new_width * (float)image_width);

            new_y = (int)
                    roundf((float)y / (float)new_height * (float)image_height);
            
            /* Avoid OoB */
            new_x = min(new_x, image_width - 1);
            new_y = min(new_y, image_height - 1);

            /* Copy pixel from original image */
            red = get_pixel(img, C_RED, new_x, new_y);
            green = get_pixel(img, C_BLUE, new_x, new_y);
            blue = get_pixel(img, C_BLUE, new_x, new_y);

            /* Set resized image pixel */
            set_pixel(resized_img, x, y, red, green, blue);
        }
    }

    return resized_img;
}

/*
** Convert image to a already created binary matrix
** Image must be already binarized to avoid unexpected output
*/
void image_to_binmatrix_fill (matrix *matrix_in, image *input_image) {
    /* Cursor position */
    unsigned int x;
    unsigned int y;

    /* Fill matrix */
    for (y = 0; y < input_image->height; y++)
    {
        for (x = 0; x < input_image->width; x++) {
            /* Image: 255 -> Matrix: 0 */
            if (get_pixel(input_image, C_RED, x, y) == 255) {
                set_value_matrix(matrix_in, x, y, 0);
            } else {
                set_value_matrix(matrix_in, x, y, 1);
            }
        }
    }
}

/*
** Create a new matrix then convert image to this binary matrix
** Image must be already binarized to avoid unexpected output
*/
matrix *image_to_binmatrix(image *input) {

    /* Check if the image exists */
    if (input == NULL) {
        printf("[Image] Image->BinMatrix: Image pointer is null!\n");
        return NULL;
    }

    /* New matrix */
    matrix *converted_matrix = create_matrix(input->width, input->height);

    image_to_binmatrix_fill(converted_matrix, input);

    return converted_matrix;
}
