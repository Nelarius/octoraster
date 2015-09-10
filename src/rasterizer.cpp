#include "rasterizer.h"
#include "int.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>    // for min, max
#include <iostream>

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
    Height_( surface->h ),
    zBuffer_( Width_*Height_, 100000.0f )
    {}

Rasterizer::~Rasterizer() {}

void Rasterizer::rasterize( const Vector4f& v0, const Vector4f& v1, const Vector4f& v2 ) {
    /*
     * Convert from normalized device coordinates to screen space coordinates
     * */
    Vector3f p0( 0.5f*(v0.x + 1.0f)*Width_, -0.5f*(v0.y - 1.0f)*Height_, v0.z );
    Vector3f p1( 0.5f*(v1.x + 1.0f)*Width_, -0.5f*(v0.y - 1.0f)*Height_, v1.z );
    Vector3f p2( 0.5f*(v2.x + 1.0f)*Width_, -0.5f*(v2.y - 1.0f)*Height_, v2.z );
    
    /*
     * Calculate edge equations
     * */
    EdgeEqn e0( p0, p1 );
    EdgeEqn e1( p1, p2 );
    EdgeEqn e2( p2, p0 );
    
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
    InterpolateVal depth( e0, v0.z, e1, v1.z, e2, v2.z );
    
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
    const unsigned int bytesPerPixel = surface_->pitch / surface_->w;
    unsigned char* pixels = ( unsigned char* ) surface_->pixels;
    pixels += minY  * surface_->pitch;
    
    for ( int i = minY; i <= maxY; i++ ) {
        pixels += minX * bytesPerPixel;
        uint32_t* p = ( uint32_t* ) pixels;
        
        for ( int j = minX; j <= maxX; j++ ) {
            
            float z = depth.eval(j, i);
            if ( zBuffer_[index_(i,j)] < z ) {
                p++;
                continue;
            }
            
            if ( e0.eval(j, i) >= 0 && e1.eval(j, i) >= 0 && e2.eval(j, i) >= 0 ) {
                zBuffer_[index_(i, j)] = z;
                unsigned char c = 255.0f - 255.0f*(0.5f*(z + 1.0f));
                *p = SDL_MapRGB( surface_->format, c, c, c );
            }
            p++;
        }
        pixels += bytesPerPixel * ( Width_ - minX );
    }
}

void Rasterizer::clear() {
    for ( std::size_t i = 0u; i < zBuffer_.size(); i++ ) {
        zBuffer_[i] = 100000.0f;
    }
}
