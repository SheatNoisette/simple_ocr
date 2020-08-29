/*
** text_reconstruction.c for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../commons/linked_list.h"

/* Get the X average size of a char in pixel */
unsigned long dt_get_average_char_size(l_list *input_pos, unsigned long number_chars) {

    unsigned long cursor;
    unsigned long char_length = 0;

    for (cursor = 0; cursor < number_chars * 4; cursor += 4) {
        /*  X2 - X1 */
        char_length += (unsigned long)(list_get_value(input_pos, cursor + 2) 
                        - list_get_value(input_pos, cursor));
    }

    return char_length / number_chars;
}

/* Get the average distance between letters */
unsigned long dt_get_average_char_spacing(l_list *input_pos, unsigned long number_chars) {

    /* Max iteration */
    unsigned long max_char;

    /* Length of the char */
    unsigned long char_length = 0;

    /* Char cursor */
    unsigned long cursor;

    /* a(x1, y1, x2, y2) - Char 1
       b(x1, y1, x2, y2) - Char 2
        | A |-space-| B |
       x1a x2a     x1b x2b
       Formula: space = x1b - x2a */
    int x2a;
    int x1b;
    int space;
    
    /* Check number of char */
    if (number_chars == 1)
        return 0;

    /* Max iteration */
    max_char = (number_chars - 1) * 4;

    for (cursor = 0; cursor < max_char; cursor += 4) {
        x2a = list_get_value(input_pos, cursor + 2);
        x1b = list_get_value(input_pos, cursor + 4);
        space = x1b - x2a;

        /* If space is <= 0 there is a \n, ignore it */
        if (space > 0)
            char_length += (unsigned long)space;
    }

    return char_length / number_chars;
}

/* From a list of positions (from r_find_char_image) reconstruct text structure
    Format: [1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 2, ...]
    1 -> A character | 0 -> Space | 2 -> \n */
l_list *deduct_text_structure (l_list *input_pos) {

    /* Count the number of char detected */
    unsigned long char_detected = 0;

    /* Create a list which will contain the text structure */
    l_list *t_structure = list_create();

    /* Number of characters present in the image */
    unsigned long number_char = list_length(input_pos) / 4;

    /* Average size of a char
    /* unsigned long average_size = dt_get_average_char_size(input_pos, number_char); */

    /* Average separation of a char (Space between two char) */
    unsigned long average_separator = dt_get_average_char_size(input_pos, number_char);

    /*  Maximum space between two char before considering it like space */
    int max_space = (int) (average_separator);

    /* Max iteration */
    unsigned long max_char = (number_char - 1) * 4;

    /* Letter spacing - Based on dt_get_average_char_spacing */
    int x2a;
    int x1b;
    int space;

    /* Char cursor */
    unsigned long cursor;
    unsigned long index;

    /* If there is at least a letter add it */
    list_add(&t_structure, 1);

    /* Build the rest of the list */
    for (cursor = 0; cursor < max_char; cursor += 4) {
        x2a = list_get_value(input_pos, cursor + 2);
        x1b = list_get_value(input_pos, cursor + 4);
        space = x1b - x2a;

        /* If space is <= 0 there is a \n */
        if (space < 0) {
            list_add(&t_structure, 2);

            /* If the list isn't empty, there is a letter after \n */
            if (cursor != max_char) {
                list_add(&t_structure, 1);
                /* Increment the number of char detected */
                char_detected++;
            }
           
        /* There is a letter */
        } else if (max_space >= space && space > 0) {
            list_add(&t_structure, 1);
            char_detected++;
        /* It's a space */
        } else if (space > max_space) {
            list_add(&t_structure, 0);
            list_add(&t_structure, 1);
            char_detected++;
        }
    }

    /* printf("Number of char: %li - Recognized: %li\n", number_char, 
       char_detected); */

    /* Add missing characters if the system missed some */
    for (index = char_detected; index < number_char - 1; index++) {
        list_add(&t_structure, 1);
    }

    return t_structure;
}
