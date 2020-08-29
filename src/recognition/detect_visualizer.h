/*
** detect_visualizer.h for OCR in src/recognition
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/
/*  Visualize data on image */

#ifndef DETECT_VISUALIZER_H
#define DETECT_VISUALIZER_H

#include "../bitmap/image.h"

/* ------------------------  */
/*  Functions */
void visu_draw_border_box (image *input, int *border_box, 
unsigned char r, unsigned char g, unsigned char b);
void visu_draw_y_char_pos (image *input, l_list *y_positions, int *border_box,
unsigned char r, unsigned g, unsigned char b);
void visu_draw_border_letter(image *input, l_list *char_list,
unsigned char r, unsigned char g, unsigned char b);
void visu_text_structure(l_list *t_structure);

#endif