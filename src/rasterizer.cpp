#include "rasterizer.h"
#include <cstdlib>
#include <cmath>
#include <limits>
#include <iostream>

struct EdgeEqn {
    EdgeEqn( const Vector2f& p0, const Vector2f& p1 )
    :   A( p0.y - p1.y ),
        B( p1.x - p0.x ),
        C( p0.x*p1.y - p1.x*p0.y ),
        baseX( p0.x ),
        baseY( p0.y ) 
        {}
        
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
    int area = e0.C + e1.C + e2.C;
    if ( area == 0 ) {
        return;
    }
    if ( area < 0 ) {
        e0.flip();
        e1.flip();
        e2.flip();
    }
    
    unsigned char* pixels = ( unsigned char* ) surface_->pixels;
    for ( int i = 0; i < Height_; i++ ) {
        unsigned int* p = (unsigned int*) pixels;
        for ( int j = 0; j < Width_; j++ ) {
            if ( e0.eval(j, i) > 0 && e1.eval(j, i)>0 && e2.eval(j, i)>0 ) {
                *p = SDL_MapRGB(surface_->format, (unsigned char)240, (unsigned char)240, (unsigned char)240);
            }
            p++;
        }
        pixels += surface_->pitch;
    }
}
