/*
** image.c for OCR in src/bitmap
**
** Made by SheatNoisette
** Login   SheatNoisette
**
** Started on  2019 SheatNoisette
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef SDL
    #include <SDL2/SDL.h>
#endif

#include "image.h"
#include "sdl_tools.h"

//Simple image structure implementation

//Use SDL ?
#ifdef SDL

/*
** Create image from SDL Surface
*/

image *sdl_surface_to_image(SDL_Surface *input) {

    //Check if the SDL_surface is valid
    if (input == NULL) {
        printf("[Image] Error while parsing: SDL_Surface is NULL\n");
        printf("[SDL] %s\n", SDL_GetError());

        return NULL;
    }

    //Set context to sdl pixel format
    SDL_PixelFormat *pixel_format = input->format;

    if (pixel_format->BytesPerPixel != 8) {
        printf("[Image] Warning: The image selected isn't 8 bpp\n");
    }

    //Get properties of the SDL_Surface
    unsigned int image_height = (unsigned int) input->h;
    unsigned int image_width = (unsigned int) input->w;
    //printf("%i %i", image_width, image_height);

    //Hold current data
    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    //Create a new image type
    image *new_image = create_image(image_width, image_height);

    //Lock surface for direct access to pixels
    SDL_LockSurface(input);

    //Convert surface to our own type
    for (unsigned int y = 0; y < image_height; y++) {
        for (unsigned int x = 0; x < image_width; x++) {

            SDL_GetRGB(
                getpixel(input, x, y), 
            pixel_format, &red, &green, &blue);

            //Assign color to pixel
            new_image->pixel[x + y*image_width].red = red;
            new_image->pixel[x + y*image_width].green = green;
            new_image->pixel[x + y*image_width].blue = blue;
        }
    }

    SDL_UnlockSurface(input);

    return new_image;
}

SDL_Surface *image_to_sdl_surface(image *input) {

    //Check if the pointer isn't null
    if (input == NULL) {
        printf("[Image] Error while parsing image: Image is NULL\n");

        return NULL;
    }
    //Get image size
    unsigned int image_width = (unsigned int) input->width;
    unsigned int image_height = (unsigned int) input->height;

    //Image RGB color
    unsigned char red, green, blue = 0;

    //Current SDL pixel
    Uint32 sdl_pixel = 0;

    //Create a SDL_surface
    SDL_Surface *sdl_surf;
    sdl_surf = SDL_CreateRGBSurfaceWithFormat(0, input->width, input->height, 
                                              8, SDL_PIXELFORMAT_RGB888); 

    //Check if the SDL_surface is valid
    if (input == NULL) {
        printf("[Image] Error while parsing: SDL_Surface is NULL\n");
        printf("[SDL] %s\n", SDL_GetError());

        return NULL;
    }

    SDL_SetSurfaceBlendMode(sdl_surf, SDL_BLENDMODE_ADD);

    //Convert surface to our own type
    for (unsigned int y = 0; y < image_height; y++) {
        for (unsigned int x = 0; x < image_width; x++) {

            //Get color from our own type
            red = input->pixel[x + y*image_width].red;
            green = input->pixel[x + y*image_width].green;
            blue = input->pixel[x + y*image_width].blue;
            
            //Create a SDL_pixel
            sdl_pixel = SDL_MapRGB(sdl_surf->format, 
                        (Uint8)red, (Uint8)green, (Uint8)blue);

            //Write to SDL_Surface
            putpixel(sdl_surf, x, y, sdl_pixel);
        }
    }

    return sdl_surf;

}

//End SDL
#endif

/*
** Create a empty image
*/

image *create_image(unsigned int width, unsigned int height) {

    //Check image size
    if (width == 0 || height == 0) {
        printf("[Image] Image size can't be smaller than 1px * 1px\n");
        
    }

    //Create an image type
    image *new_image = malloc(sizeof(image));

    //Check malloc
    if (new_image == NULL) {
        printf("[Image] Failed to create an image\n");

        return NULL;
    }

    //Set his proprieties
    new_image->height = height;
    new_image->width = width;

    //Allocate size for pixels pointers
    new_image->pixel = malloc(sizeof(pixel) * height * width);

    //Check if pixel table is created
    if (new_image->pixel == NULL) {
        printf("[Image] Failed to allocate pixel array\n");

        return NULL;
    }

    //Clear pixels, malloc don't always gives clean mem
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            set_pixel_safe(new_image, x, y, 0, 0, 0);
        }
    }
    

    return new_image;
}


/*
** Get pixel from image
*/
unsigned char get_pixel
(image *input, color_i col, unsigned int x, unsigned int y) {

    int position = x + input->width*y;

    //Get per channel
    if (col == C_RED)
        return input->pixel[position].red;

    if (col == C_GREEN)
        return input->pixel[position].green;
    
    return input->pixel[position].blue;
}

/*
** Get pixel from image safer
*/
unsigned char get_pixel_safe
(image *input, color_i col, unsigned int x, unsigned int y) {

    //Check if the image is NULL
    if (input == NULL) {
        printf("[Image] get_pixel_safe: Image pointer is NULL\n");
        return 0;
    }

    //Check if requested exists
    if (x > input->width - 1 || y > input->height - 1) {
        printf("[Image] get_pixel_safe: Absurd coordinates x: %u y: %u\n",x,y);
        printf("[Image] Img size: x: %u y: %u\n", input->width, input->height);
        return 0;
    }

    return get_pixel(input, col, x, y);
}

/*
** Write pixel
*/
void set_pixel (
    image *input, unsigned int x, unsigned int y, 
    unsigned char r, unsigned char g, unsigned char b
) {

    int position = x + input->width*y;

    //Set channel color
    input->pixel[position].red = r;
    input->pixel[position].green = g;
    input->pixel[position].blue = b;
}

/*
** Write pixel a safer and slower
*/
void set_pixel_safe (
    image *input, unsigned int x, unsigned int y, 
    unsigned char r, unsigned char g, unsigned char b
) {
    //Check if the image is NULL
    if (input == NULL) {
        printf("[Image] set_pixel_safe: Image pointer is NULL\n");
        return;
    }

    //Check if requested exists
    if (x > input->width - 1 || y > input->height - 1) {
        printf("[Image] set_pixel_safe: Absurd coordinates x: %u y: %u\n",x,y);
        printf("[Image] Img size: x: %u y: %u\n", input->width, input->height);
        return;
    }

    //Write to pixel
    set_pixel(input, x, y, r, g, b);
}
/*
** Free image from memory
*/

void free_image(image *input) {

    if (input == NULL) {
        printf("[Image] Impossible to release an invalid image\n");

        return;
    }

    //Free pixels
    free(input->pixel);

    //Free image
    free(input);
}