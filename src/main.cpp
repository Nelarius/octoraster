#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif
#include <stdio.h>

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
            800, 600,
            0);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
    if (windowSurface->format->BytesPerPixel < 4)
    {
        printf("Invalid pixel format.\n");
        SDL_DestroyWindow(window);
        return 2;
    }

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
        static int c = 0;
        if (!SDL_LockSurface(windowSurface))
        {
            unsigned char* pixels = (unsigned char*)windowSurface->pixels;
            for (int y = 0; y < windowSurface->h; y++)
            {
                unsigned int* p = (unsigned int*)pixels;
                for (int x = 0; x < windowSurface->w; x++)
                {
                   *p++ = SDL_MapRGB(windowSurface->format, (unsigned char)((y>>2)&0xff), (unsigned char)((x>>2)&0xff), (unsigned char)(255-c));
                }
                pixels += windowSurface->pitch; // move pointer to the next row
            }
            c = (c + 1) & 0xff;

            SDL_UnlockSurface(windowSurface);
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
