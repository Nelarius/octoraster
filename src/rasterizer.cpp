#include "rasterizer.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>    // for min, max
#include <iostream>
#include "int.h"

struct EdgeEqn {
    public:
        EdgeEqn( const Vector3f& p0, const Vector3f& p1 )
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

struct InterpolateVal {
    public:
        InterpolateVal( const EdgeEqn& e0, float v0, const EdgeEqn& e1, float v1, const EdgeEqn& e2, float v2 ) {
            float area = 0.5f * ( e0.C + e1.C + e2.C );
            A = 0.5f * ( v0*e0.A + v1*e1.A + v2*e2.A ) / area;
            B = 0.5f * ( v0*e0.B + v1*e1.B + v2*e2.B ) / area;
            C = 0.5f * ( v0*e0.C + v1*e1.C + v2*e2.C ) / area;
        }
        
        float eval( int x, int y ) const {
            return A*x + B*y + C;
        }
        
        float A;
        float B;
        float C;
    
    private:
        InterpolateVal() {}
        
};

Rasterizer::Rasterizer( SDL_Surface* surface )
:   surface_( surface ),
    Width_( surface->w ),
    Height_( surface->h )
    {}

Rasterizer::~Rasterizer() {}

void Rasterizer::scanTriangle( const Vector3f& p0, const Vector3f& p1, const Vector3f& p2 ) {
    EdgeEqn e0( p0, p1 );
    EdgeEqn e1( p1, p2 );
    EdgeEqn e2( p2, p0 );
    
    float depth0 = p0.z*255.0f;
    float depth1 = p1.z*255.0f;
    float depth2 = p2.z*255.0f;
    
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
     * get the equations for interpolating a floating point value across 
     * the triangle face
     * */
    InterpolateVal color( e0, depth0, e1, depth1, e2, depth2 );
    
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
     * scan the triangle within the bounding box
     * */
    unsigned int bytesPerPixel = surface_->pitch / surface_->w;
    unsigned char* pixels = ( unsigned char* ) surface_->pixels;
    pixels += minY  * surface_->pitch;
    
    for ( int i = minY; i <= maxY; i++ ) {
        pixels += minX * bytesPerPixel;
        uint32_t* p = ( uint32_t* ) pixels;
        
        for ( int j = minX; j <= maxX; j++ ) {
            if ( e0.eval(j, i) > 0 && e1.eval(j, i) > 0 && e2.eval(j, i) > 0 ) {
                unsigned char c = color.eval( j, i );
                *p = SDL_MapRGB(surface_->format, c, c, c );
            }
            p++;
        }
        pixels += bytesPerPixel * ( Width_ - minX );
    }
}
