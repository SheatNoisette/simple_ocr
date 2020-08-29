/*
** para_detect.c for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/
/* Paragraph detection */

#include <stdio.h>
#include <stdlib.h>

#include "../bitmap/image.h"
#include "../bitmap/image_drawing.h"
#include "../commons/linked_list.h"
#include "char_detect.h"

/*
** Find text border and give an array
*/

int *r_get_paragraph_border(image *img) {

    /* Cursor used troughout the algorithm */
    int x_cursor = 0;
    int y_cursor = 0;

    /* Get image size */
    int image_width = img->width;
    int image_height = img->height;

    /* Create array that gives paragraph border (4 -> x1, y1, x2, y2) */
    int *border = malloc(4 * sizeof(int)); 
    
    /* Check malloc */
    if (border == NULL) {
    fprintf(stderr,"[char_detect] Failed to allocate memory to border array");
        return NULL;
    }

    /* Clear values */
    border[0] = 0; /* x1 */
    border[1] = 0; /* y1 */
    border[2] = 0; /* x2 */
    border[3] = 0; /* y2 */

    /* ----------------- */
    /* Find top */ 

    while (y_cursor < image_height 
        && !r_find_pixel_horizontal(img, 0, y_cursor, image_width)) {
        y_cursor++;
    }

    /* Found top (Maybe) */
    border[1] = y_cursor;

    /* Reset cursor */

    /* ----------------- */
    /* Find bottom */

    /* Set cursor at the */
    y_cursor = image_height - 1;

    while (y_cursor > 0
        && !r_find_pixel_horizontal(img, 0, y_cursor, image_width)) {
        y_cursor--;
    }

    /* Found bottom ? */
    border[3] = y_cursor;

    /* ------------------ */
    /* Find left */

    while (x_cursor < image_height
        && !r_find_pixel_vertical(img, x_cursor, 0, image_height) ) {
        x_cursor++;
    }

    /* Found left */
    border[0] = x_cursor;

    /* ------------------ */
    /* Find right */
    /* Set cursor to right */
    x_cursor = image_width - 1;

    while (x_cursor > 0
        && !r_find_pixel_vertical(img, x_cursor, 0, image_height) ) {
        x_cursor--;
    }

    /* Found right */
    border[2] = x_cursor;

    return border;
}