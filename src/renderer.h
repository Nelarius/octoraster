#ifndef RENDERER_H
#define RENDERER_H

#include "rasterizer.h"
#include "vector.h"
#include "matrix.h"
#include "int.h"
#include <vector>

struct OrthoCamera {
    float near, far, width, height;
};

void Render( Rasterizer&, const std::vector< Vector4f >&, const Matrix4f&, const OrthoCamera& );


#endif