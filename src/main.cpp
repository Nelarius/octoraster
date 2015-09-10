#ifdef _MSC_VER
#   include <SDL.h>
#else
#   include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "rasterizer.h"
#include "renderer.h"
#include "matrix.h"
#include "quaternion.h"
#include "int.h"

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
    
    /*
     * Create rasterizer
     * */
     Rasterizer rasterizer( SDL_GetWindowSurface( window ) );
    
    /*
     * craete triangle instance
     * */
    std::vector< Vector4f > triangle;
    triangle.push_back( Vector4f( -5.0f, -2.5f, 0.0f, 1.0f ) );
    triangle.push_back( Vector4f( 5.0f, -2.5f, 0.0f, 1.0f ) );
    triangle.push_back( Vector4f( 0.0f, 2.5f, 0.0f, 1.0f ) );
    
    /*
     * set model orientation
     * */
    Quatf orientation = Quatf::Identity();
    Quatf delta( sin(0.004f), 0.0f, 0.0f, cos(0.004f) );
    Matrix4f model1( 
        1.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, -5.0f, 
        0.0f, 0.0f, 0.0f, 1.0f 
    );
    Matrix4f model2( 
        1.0f, 0.0f, 0.0f, 1.5f, 
        0.0f, 1.0f, 0.0f, 1.5f, 
        0.0f, 0.0f, 1.0f, -6.0f, 
        0.0f, 0.0f, 0.0f, 1.0f 
    );
    OrthoCamera camera;
    camera.near = 0.0f;
    camera.far = 10.0f;
    camera.width = 20.0f;
    camera.height = 15.0f;
    
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
                uint32_t* p = ( uint32_t* ) pixels;
                for ( int j = 0; j < windowSurface->w; j++ ) {
                    *p++ = SDL_MapRGB( windowSurface->format, 0, 0, 0 );
                }
                pixels += windowSurface->pitch;
            }
            /*
             * render the triangles
             * */
            orientation = orientation * delta;
            // this one is deeper
            Render( rasterizer, triangle, model2 * Quatf( 0.0f, 0.0f, sin(0.3f), cos(0.3f) ).asMatrix(), camera );
            Render( rasterizer, triangle, model1 * orientation.asMatrix(), camera );  // this is deeper
            rasterizer.clear();
            
            SDL_UnlockSurface(windowSurface);
        }
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
