#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <SDL2/SDL_surface.h>
#include "vector.h"
#include "assert.h"
#include <vector>

/**
 * @class Rasterizer
 * @date 09/09/15
 * @file rasterizer.h
 * @brief Rasterizes triangles using edge equations.
 */
class Rasterizer {
    public:
        Rasterizer( SDL_Surface* surface );
        ~Rasterizer();
        
        /**
         * @brief Rasterize a triangle with three vertices in normalized device coordinates.
         * @param p1
         * @param p2
         * @param p3
         */
        void rasterize( const Vector4f& p1, const Vector4f& p2, const Vector4f& p3 );
        
        /**
         * @brief Clear the depth buffer.
         */
        void clear();
        
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
        std::vector<float> zBuffer_;
};

#endif