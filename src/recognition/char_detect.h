/*
** char_detect.h for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef CHAR_DETECT_H
#define CHAR_DETECT_H

#include "../bitmap/image.h" 
#include "../commons/linked_list.h" 

/* ------------------------- */
/* Functions */

char r_find_pixel_horizontal
(image *input, unsigned int x_from, unsigned int y, unsigned int x_to);


l_list *r_find_char_y(image *img, unsigned int x_from, unsigned x_to);

unsigned char r_find_pixel_vertical
(image *img, unsigned int x, unsigned int y_from, unsigned int y_to);

l_list *r_find_char_image(image *input, l_list *y_lines);

#endif