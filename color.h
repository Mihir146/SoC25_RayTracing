#ifndef COLOR_H
#define COLOR_H
#include"vec3.h"
#include"interval.h"

//#include<iostream>
using color = vec3;

//pixel_color vector should have components in the range [0,1] only 
void write_color(std::ostream& out, const color& pixel_color){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    //output to stdout
    out<<rbyte<<' '<<gbyte<<' '<<bbyte<<'\n';
}
#endif
