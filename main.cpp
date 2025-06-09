#include<iostream>
#include"vec3.h"
#include"color.h"
#include"ray.h"

color ray_color(const ray& r){
    return color(0,0,0);
}

int main(){
    auto aspect_ratio = 16.0/9.0;
    int img_width = 400;

    //calculate the image height and let it be atleast 1px
    int img_height = aspect_ratio * img_width;
    img_height = (img_height < 1)? 1:img_height;

    //setup the viewport dimensions
    auto viewport_height = 2.0;
    ////okay if the viewport width is less than 1 as it can be a real number
    auto viewport_width = viewport_height * (double(img_width)/img_height); 

    //this is the camera implementation!
    

}
