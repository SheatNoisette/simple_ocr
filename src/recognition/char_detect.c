/*
** char_detect.c for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdio.h>

#include "../bitmap/image.h"
#include "../bitmap/image_drawing.h"
#include "../commons/linked_list.h"

// Find characters in image

/*
** Detect black pixel vertically
** Return 1 if found or 0 if none
** Search from 'x_from' to 'x_to' at 'y' height
** THE IMAGE MUST BE BINARIZED!
*/

char r_find_pixel_horizontal(image *input, unsigned int x_from, unsigned int y,
                             unsigned int x_to)
{
    // From
    unsigned int x_cursor = x_from;

    // Check if we found a char
    while (x_cursor < x_to && get_pixel(input, C_RED, x_cursor, y) == 255)
    {
        x_cursor++;
    }

    return x_to != x_cursor;
}

/*
** Find character horizontally
** Search from y_from to y_to at x
** THE IMAGE MUST BE BINARIZED!
*/

unsigned char r_find_pixel_vertical(image *img, unsigned int x,
                                    unsigned int y_from, unsigned int y_to)
{
    unsigned y_cursor = y_from;

    while (y_cursor < y_to && get_pixel(img, C_RED, x, y_cursor) == 255)
    {
        y_cursor++;
    }

    return y_to != y_cursor;
}

/*
** Find a char in vertically
** x_from and x_to are used to reduce the number of pixel checking
** this must be computed before
*/
///!\TODO: Get data and put it in a list

l_list *r_find_char_y(image *img, unsigned int x_from, unsigned x_to)
{
    int image_height = img->height;
    int y_cursor = 0;
    l_list *y_positions = list_create();
    // detect_y_List = []
    // We found a line ?
    unsigned char line_recognised = 0;
    // Found a pixel ?
    unsigned char detected_pixel = 0;

    while (y_cursor < image_height)
    {
        detected_pixel = r_find_pixel_horizontal(img, x_from, y_cursor, x_to);

        if (detected_pixel && !line_recognised)
        {
            line_recognised = 1;

            // image_draw_line_h(img, 0, img->width, y_cursor, 255, 0, 0);
            list_add(&y_positions, y_cursor);
            // detect_ylist.append(y_cursor)
        }
        else if (!detected_pixel && line_recognised)
        {
            line_recognised = 0;

            // image_draw_line_h(img, 0, img->width, y_cursor, 255, 0, 0);
            list_add(&y_positions, y_cursor - 1);
            // detect_y_list.append(y_cursor - 1)
        }
        // If we are at the end of the array and the line isn't finished
        else if (y_cursor == image_height && line_recognised)
        {
            // image_draw_line_h(img, 0, img->width, y_cursor, 255, 0, 0);
            // detectY.append(img->width - 1)
            list_add(&y_positions, img->width - 1);
        }

        y_cursor++;
    }

    return y_positions;
}

/*
** Find every char in every line
** input image and y line get from r_find_char_y
*/

l_list *r_find_char_image(image *input, l_list *y_lines)
{
    // Get image length
    size_t list_len = list_length(y_lines);
    // Found a pixel in x ?
    unsigned char found_pixel = 0;
    // Found a char ?
    unsigned char found_char = 0;
    // Current y line cursor
    size_t current_cursor = 0;
    // Current x position
    size_t current_x = 0;
    // No need to go further
    size_t max_x = input->width;
    // List to hold data for char position - x1, y1, x2, y2, ...
    l_list *char_pos = list_create();

    // Check for errors such as invalid data
    if (input->width == 0 || input->height == 0)
        return NULL;
    if (list_len % 2 != 0 || list_len == 0)
        return NULL;

    // Check for every line detected
    while (current_cursor < list_len)
    {
        // Reset current x - Pixel detection
        current_x = 0;

        // Go left to right
        while (current_x < max_x)
        {
            // Find a pixel
            found_pixel = r_find_pixel_vertical(
                input, current_x, list_get_value(y_lines, current_cursor),
                list_get_value(y_lines, current_cursor + 1));

            // End of the char
            if (found_char && !found_pixel)
            {
                // Reset found char
                found_char = 0;

                // Push x2, y2
                list_add(&char_pos, current_x - 1);
                list_add(&char_pos,
                         list_get_value(y_lines, current_cursor + 1));

                // Char detected first time
            }
            else if (!found_char && found_pixel)
            {
                // Set flag found char
                found_char = 1;
                // Add x1 then y1
                list_add(&char_pos, current_x);
                list_add(&char_pos, list_get_value(y_lines, current_cursor));

                // Check if we are at the end of the image
            }
            else if (current_x == max_x - 1 && found_char)
            {
                found_char = 0;
                // Add x1 then y1
                list_add(&char_pos, current_x);
                list_add(&char_pos, list_get_value(y_lines, current_cursor));
            }

            current_x++;
        }

        current_cursor += 2;
    }

    // Get chars
    return char_pos;
}