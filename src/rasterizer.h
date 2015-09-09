#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <vector>
#include <SDL2/SDL_surface.h>
#include "vector.h"
#include "assert.h"

typedef Vector2<int> Vector2i;

/**
 * @class Rasterizer
 * @date 09/09/15
 * @file rasterizer.h
 * @brief Rasterizes triangles using edge equations.
 * 
 */
class Rasterizer {
    public:
        Rasterizer( SDL_Surface* surface );
        ~Rasterizer();
        
        void scanTriangle( const Vector3f& p1, const Vector3f& p2, const Vector3f& p3 );
        
    private:
        Rasterizer();
        
        inline int index_( int i, int j ) const {
            int r = i*surface_->w + j;
            ASSERT( r < surface_->w*surface_->h, "Index out of bounds" );
            return r;
        }
        
        SDL_Surface* surface_;
        const int Width_;
        const int Height_;
};

#endif