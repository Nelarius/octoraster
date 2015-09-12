# rasterizer

A small triangle rasterizer with a depth buffer.

## Build

Written in C++98. The code has been tested using gcc on Linux and Windows.

## A small overview

The rasterizer uses edge equations to quickly test whether a pixel is in the triangle or not. Values defined at the vertices can be interpolated across the triangle face.

* all the rasterization logic is in `src/rasterizer.cpp`
* a bounding box is computed for the triangle, and only pixels within the bounding box are tested.
* many unnecessary calculations are moved out of the rasterization loop. For instance, evaluating which half-plane the pixel is in requires the calculation of `f(x, y) = A(x - x0) + B(y - y0)`. We can move this calculation out of the loop and replace it with a single addition by using the property `f(x+1, y) - f(x, y) = A`, and `f(x, y+1) - f(x, y) = B`.