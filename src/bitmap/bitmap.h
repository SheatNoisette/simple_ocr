#ifndef BITMAP_H
#define BITMAP_H
#include "image.h"

image *bitmaploader(char* path);
unsigned int size_header(char *start,char reverse);
image *pixelize(image *image_to_change,char *start,char reverse, unsigned int size, int height,int width);
unsigned short bits_by_pixel(char *start,char reverse);
int image_w_h(char *start,char reverse);
image *bitmap_d(char* path);

#endif
