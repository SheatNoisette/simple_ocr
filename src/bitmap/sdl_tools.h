/* 
 * Tools to manipulate any surface in SDL
 * http:// sdl.beuc.net/sdl.wiki/Pixel_Access
 * THIS CODE IS GPL2 LICENSED
*/


#ifndef SDL_TOOLS_H
#define SDL_TOOLS_H

/* Disable if no sdl support */
    #ifdef SDL
        /* Get SDL types */
        #include <SDL2/SDL.h>

        Uint32 getpixel(SDL_Surface *surface, int x, int y);

        void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

    #endif
#endif