#include <err.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#ifdef SDL
#    include <SDL2/SDL.h>
#endif

/*
** bitmap.c for OCR in src/bitmap.c
**
** Made by jpbinger
** Login   jpbinger
**
** Started on  2019 jpbinger
*/

/*
** structure of the header
*/
#pragma pack(1)
typedef struct
{
    uint16_t filetype; // two bytes saying the type of file
    uint32_t size; // the size of the file
    uint16_t reserved; // reserved file
    uint16_t reserved2; // reserved file
    uint32_t offset; // the offset between the start of the file and the pixel
                     // description
    uint32_t dib; // dib define the order of the rest of the header
    int32_t width; // width of the image
    int32_t height; // height of the image
    uint16_t planes; // number of planes
    uint16_t bits_ppix; // bits per pixels
    uint32_t compression; // type of compression
    uint32_t image_size; // size of the image
    int32_t xppm; // pixel per meter in the x axe
    int32_t yppm; // pixel per meter in the y axe
    uint32_t num_colors; // number of colors
    uint32_t important_colors; // important colors
} BITmap_Header;

typedef struct
{
    BITmap_Header header;
    unsigned char *pixels_data;
} Image_data;

/*
** change the pixels of the image from a chain of bits
** return the image changed
*/
image *pixelize(image *image_to_change, char *start, int height, int width)
{
    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            set_pixel(image_to_change, x, y, *(start + 2), *(start + 1),
                      *(start));
            start = start + 3;
        }

        if ((width * 3) % 4)
        {
            start = start + (4 - (width * 3) % 4);
        }
    }

    return image_to_change;
}

image *passage_by_sdl(char *path, BITmap_Header *header)
{
#ifdef SDL
    // processing with SDL

    SDL_Surface *imagesdl = SDL_LoadBMP(path);

    // free the header

    free(header);

    // transform the sdl into our format

    image *image = sdl_surface_to_image(imagesdl);

    // free the SDL_surface created by the process of SDL

    SDL_FreeSurface(imagesdl);

    // return the bitmap in the format image

    return image;
#else
    if (path == NULL)
    {
        errx(404, "there is no path to the file");
    }
    if (header == NULL)
    {
        errx(405, "Header is missing");
    }
    return NULL;
#endif
}

image *bitmaploader(char *path)
{
    // create a verification value
    size_t test;
    // create the image and the header. then make a copy of the header

    image *image;
    BITmap_Header *he = (BITmap_Header *)malloc(54 * sizeof(char));
    BITmap_Header *p = he;

    // create the filestream

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        errx(404, "fichier non lu");
    }

    // read the file and introduce it in the pointer of the BITmap_Header
    test = fread(p, 1, 54, file);

    // check if the file was read correctly
    if (test != 54)
    {
        errx(12, "Can't read file");
    }

    // check if the file is a bitmap type if not it return an error
    if (he->filetype != 0x4d42)
    {
        if (he->filetype == 0x4142 || he->filetype == 0x4943
            || he->filetype == 0x4349 || he->filetype == 0x5043
            || he->filetype == 0x5450)
        {
            // return a warning to inform that it can't be used by our loader
            // and will be processed by SDL
            fprintf(stdout,
                    "[bitmap] Warning: Type error not BM signature but still a "
                    "bitmap falling back to SDL\n");

// make a passage by sdl if possible
#ifdef SDL
            image = passage_by_sdl(path, he);

            // return the bitmap in the format image
            return image;
#else
            errx(42, "SDL is not enabled");
#endif
        }
        errx(1, "not a bitmap of type BM");
    }

    /*
    ** Check if the image has a certain dib dib = 40 is the only one for the
    *moment
    ** If not the image is given to charge to SDL
    */
    if (he->dib != 40)
    {
        // return a warning to inform that it can't be used by our loader and
        // will be processed by SDL
        fprintf(stdout, "[bitmap] Warning: DIB error falling back to SDL\n");

// make a passage by sdl if possible
#ifdef SDL
        image = passage_by_sdl(path, he);

        // return the bitmap in the format image
        return image;
#else
        errx(42, "SDL is not enabled");
#endif
    }

    /*
    **check if the image has 24 bits per pixels
    **if not the image is given to charge to SDL
    */

    if (he->bits_ppix != 24)
    {
        // return a warning to inform that it can't be used by our loader and
        // will be processed by SDL

        fprintf(
            stdout,
            "[bitmap] Warning: Bits per pixels error falling back to SDL\n");

// make a passage by sdl if possible
#ifdef SDL
        image = passage_by_sdl(path, he);

        // return the bitmap in the format image
        return image;
#else
        errx(42, "SDL is not enabled");
#endif
    }

    /*
    **check if the image has the compression set to 0
    **0 means the file is not compressed
    **if not the image is given to charge to SDL
    */

    if (he->compression != 0)
    {
        // return a warning to inform that it can't be used by our loader and
        // will be processed by SDL

        fprintf(
            stdout,
            "[bitmap] Warning: Bits per pixels error falling back to SDL\n");

// make a passage by sdl if possible
#ifdef SDL
        image = passage_by_sdl(path, he);

        // return the bitmap in the format image
        return image;
#else
        errx(42, "SDL is not enabled");
#endif
    }

    // create an image with the width and height of image

    image = create_image(he->width, he->height);

    // create the pointer for the binary data

    char *pixels = (char *)malloc(he->image_size * sizeof(char));
    test = fread(pixels, 1, he->image_size, file);

    // check if the file was read correctly

    if (test != he->image_size)
    {
        errx(12, "Can't read file");
    }

    // copy of the pointer

    char *pix = pixels;

    // use pixelize to put the pixels of the bitmap in their places

    image = pixelize(image, pix, he->height, he->width);

    // free the different pointers

    free(pixels);
    free(he);

    // return the bitmap in the format image

    return image;
}
