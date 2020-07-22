/*
** image_drawing.c for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

//Draw simple figure in our image type

#ifndef IMAGE_DRAWING_H
#define IMAGE_DRAWING_H

//Include our image type
#include "image.h"

//-------------------------
// Functions

void image_draw_line_h
(image *input, unsigned int x1, unsigned int x2, unsigned int y, 
unsigned char r,  unsigned char g,  unsigned char b);


void image_draw_line_v
(image *input, unsigned int x, unsigned int y1, unsigned int y2, 
unsigned char r,  unsigned char g,  unsigned char b);

void image_draw_rectangle
(image *input, 
unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, 
unsigned char r, unsigned char g, unsigned char b);

#endif