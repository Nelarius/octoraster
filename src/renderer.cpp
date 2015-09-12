#include "renderer.h"
#include <cstdlib>

Matrix4f OrthoProjection( const OrthoCamera& c ) {
    return Matrix4f(
        2.0f/c.width,   0.0f,           0.0f,                       0.0f,
        0.0f,           2.0f/c.height,  0.0f,                       0.0f,
        0.0f,           0.0f,           2.0f / (c.near - c.far),    (c.near + c.far) / (c.near - c.far),
        0.0f,           0.0f,           0.0f,                       1.0f
    );
}

void Render( Rasterizer& r, const std::vector< Vector4f >& buffer, const Matrix4f& model, const OrthoCamera& c ) {
    for ( std::size_t i = 0u; i < buffer.size(); i += 3 ) {
        Vector4f v1 = OrthoProjection( c ) * model * buffer[i];
        Vector4f v2 = OrthoProjection( c ) * model * buffer[i+1];
        Vector4f v3 = OrthoProjection( c ) * model * buffer[i+2];
        r.rasterize( v1, v2, v3 );
    }
}
