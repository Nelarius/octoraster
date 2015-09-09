#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include "rasterizer.h"

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL init failed.\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Umbra Assignment",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            600, 400,
            0);
    
    Rasterizer rasterizer( SDL_GetWindowSurface( window ) );
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    if (windowSurface->format->BytesPerPixel < 4)
    {
        printf("Invalid pixel format.\n");
        SDL_DestroyWindow(window);
        return 2;
    }

    srand( time(0) );
    const float RandMax = RAND_MAX;

    // Main loop
    bool quit = false;
    while (!quit) 
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))  
        {
            if (event.type == SDL_QUIT) { 
                quit = true;
            }
        }
        
        if (!SDL_LockSurface(windowSurface))
        {   
            /*
             * clear the screen here
             * */
            unsigned char* pixels = (unsigned char*) windowSurface->pixels;
            for ( int i = 0; i < windowSurface->h; i++ ) {
                unsigned int* p = (unsigned int*) pixels;
                for ( int j = 0; j < windowSurface->w; j++ ) {
                    *p++ = SDL_MapRGB( windowSurface->format, 0, 0, 0 );
                }
                pixels += windowSurface->pitch;
            }
            /*
             * rasterize random triangles here
             * */
            rasterizer.scanTriangle( Vector2f( 600.0f*rand()/RandMax, 400.0f*rand()/RandMax ), Vector2f( 600.0f*rand()/RandMax, 400.0f*rand()/RandMax ), Vector2f( 600.0f*rand()/RandMax, 400.0f*rand()/RandMax ) );
            
            SDL_UnlockSurface(windowSurface);
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
