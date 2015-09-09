#include "rasterizer.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>    // for min, max
#include <iostream>

struct EdgeEqn {
    EdgeEqn( const Vector2f& p0, const Vector2f& p1 )
    :   A( p0.y - p1.y ),
        B( p1.x - p0.x ),
        C( p0.x*p1.y - p1.x*p0.y ),
        baseX( p0.x ),
        baseY( p0.y )  {}
        
    inline int eval( int x, int y ) const {
        return A*( x - baseX ) + B*( y - baseY );
    }
    
    inline void flip() {
        A = -A;
        B = -B;
        C = -C;
    }
    
    int A;
    int B;
    int C;
    
    private:
        EdgeEqn() {}
        
        int baseX;
        int baseY;
};

Rasterizer::Rasterizer( SDL_Surface* surface )
:   surface_( surface ),
    Width_( surface->w ),
    Height_( surface->h )
    {}

Rasterizer::~Rasterizer() {}

void Rasterizer::scanTriangle( const Vector2f& p0, const Vector2f& p1, const Vector2f& p2 ) {
    EdgeEqn e0( p0, p1 );
    EdgeEqn e1( p1, p2 );
    EdgeEqn e2( p2, p0 );
    
    /*
     * compute triangle bounding box
     * */
    int minX, maxX, minY, maxY;
    minX = floor( std::min( p0.x, std::min( p1.x, p2.x ) ) );
    maxX = ceil( std::max( p0.x, std::max( p1.x, p2.x ) ) );
    minY = floor( std::min( p0.y, std::min( p1.y, p2.y ) ) );
    maxY = ceil( std::max( p0.y, std::max( p1.y, p2.y ) ) );
    
    /*
     * clip againts screen bounds
     * */
    minX = std::max( minX, 0 );
    maxX = std::min( maxX, Width_ - 1 );
    minY = std::max( minY, 0 );
    maxY = std::min( maxY, Height_ - 1 );
    
    /*
     * a positive area implies that the positive half-planes defined by the edge equations
     * are oriented into the triangle.
     * 
     * C, or the area of the subtriangle, is always positive when in the positive half plane.
     * */
    int area = e0.C + e1.C + e2.C;
    if ( area == 0 ) {
        return;
    }
    if ( area < 0 ) {
        e0.flip();
        e1.flip();
        e2.flip();
    }
    
    /*
     * scan the triangle within the bounding box
     * */
    unsigned int bytesPerPixel = surface_->pitch / surface_->w;
    unsigned char* pixels = ( unsigned char* ) surface_->pixels;
    pixels += minY  * surface_->pitch;
    for ( int i = minY; i <= maxY; i++ ) {
        pixels += minX * bytesPerPixel;
        unsigned int* p = (unsigned int*) pixels;
        for ( int j = minX; j <= maxX; j++ ) {
            if ( e0.eval(j, i) > 0 && e1.eval(j, i) > 0 && e2.eval(j, i) > 0 ) {
                *p = SDL_MapRGB(surface_->format, 240, 240, 240 );
            }
            p++;
        }
        pixels += bytesPerPixel * ( Width_ - minX );
    }
}
