/*
** image.h for OCR in src/filters
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#ifndef IMAGE_H
#define IMAGE_H

//SDL Support
#ifdef SDL
    #include <SDL2/SDL.h>
#endif

//----------------------------
// Structures

typedef struct image_pixel pixel;
typedef struct image_pixel color;
typedef struct image image;

struct image_pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

struct image {
    unsigned int width;
    unsigned int height;
    pixel *pixel;
};

typedef enum  {
    C_RED,
    C_GREEN,
    C_BLUE
} color_i;

//----------------------------

//SDL Support
#ifdef SDL
    image *sdl_surface_to_image(SDL_Surface *input);

    SDL_Surface *image_to_sdl_surface(image *input);
#endif

image *create_image(unsigned int width, unsigned int height);

void free_image(image *input);

unsigned char get_pixel (
    image *input, color_i col, unsigned int x, unsigned int y
);

unsigned char get_pixel_safe (
    image *input, color_i col, unsigned int x, unsigned int y
);

void set_pixel (
    image *input, unsigned int x, unsigned int y, 
    unsigned char r, unsigned char g, unsigned char b
);

void set_pixel_safe (
    image *input, unsigned int x, unsigned int y, 
    unsigned char r, unsigned char g, unsigned char b
);

#endif