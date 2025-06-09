#ifndef COLOR_H
#define COLOR_H
#include"vec3.h"
#include<iostream>

using color = vec3;

//pixel_color vector should have components in the range [0,1] only 
void write_color(std::ostream& out, const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //translate the [0,1] components to [0,255] range
    int rbyte = int(255.999*r);
    int gbyte = int(255.999*g);
    int bbyte = int(255.999*b);

    //output to stdout
    out<<rbyte<<' '<<gbyte<<' '<<bbyte<<'\n';
}
#endif
