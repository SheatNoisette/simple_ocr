/*
** image_drawing.c for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdlib.h>
#include <stdio.h>
#include "image.h"

/*
 * Draw simple figure in our image type
 */

/*
** Draw a line from x1 to x2 in y pos vertically
*/

void image_draw_line_h
(image *input, unsigned int x1, unsigned int x2, unsigned int y, 
unsigned char r,  unsigned char g,  unsigned char b)  {
    /* Cursor */
    unsigned int current_x;

    /* Draw a line from x1 -> x2 */
    for (current_x = x1; current_x < x2; current_x++) {
        set_pixel(input, current_x, y, r, g, b);
    }
}


/*
** Draw a line from y1 to y2 in x pos horizontally
*/

void image_draw_line_v
(image *input, unsigned int x, unsigned int y1, unsigned int y2, 
unsigned char r,  unsigned char g,  unsigned char b)  {
    /* Cursor */
    unsigned int current_y = y1;
    /* Draw a line from y1 -> y2 */
    for (current_y = y1; current_y < y2; current_y++) {
        set_pixel(input, x, current_y, r, g, b);
    }
}

/*
** Draw a rectangle
** Coordinates: x1, y1, x2, y2
*/

void image_draw_rectangle
(image *input, 
unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, 
unsigned char r, unsigned char g, unsigned char b) {

    /* Check coordinates */
    if (x1 > x2 || y1 > y2) {
        printf("[image_drawing] Wrong coordinates - Rectangle");
        return;
    }

    /* Draw a rectangle */

    /* Top */
    image_draw_line_h(input, x1, x2, y1, r, g, b);   
    /* Bottom */
    image_draw_line_h(input, x1, x2, y2, r, g, b);
    /* Left */
    image_draw_line_v(input, x1, y1, y2, r, g, b);
    /* Right */
    image_draw_line_v(input, x2, y1, y2, r, g, b);

}