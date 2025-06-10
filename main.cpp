#include<iostream>
#include"vec3.h"
#include"color.h"
#include"ray.h"

color ray_color(const ray& r){
    vec3 unit_direction = r.direction().unit();
    //a should be b/w 0 and 1 and y comp of unit_direction is b/w -1 and 1 so we making sure to adjust it 
    auto a = 0.5*(unit_direction.y() + 1.0);
    //lerping b/w white and blue (look up the form of lerp)
    return (1.0 - a)*(color(1.0,1.0,1.0)) + (a)*(color(0.5, 0.7, 1.0));
}

int main(){
    //aspect ratio is ratio width/height
    auto aspect_ratio = 16.0/9.0;
    int img_width = 400;

    //calculate the image height and let it be atleast 1px
    int img_height = int(img_width / aspect_ratio);
    img_height = (img_height < 1)? 1:img_height;

    //setup the viewport dimensions
    auto viewport_height = 2.0;
    ////okay if the viewport width is less than 1 as it can be a real number
    auto viewport_width = viewport_height * (double(img_width)/img_height); 

    //this is the camera implementation!
    auto focal_length = 1.0;
    auto camera_center = point3(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width,0,0);
    auto viewport_v = vec3(0,-viewport_height,0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u/img_width;
    auto pixel_delta_v = viewport_v/img_height;
   
    //local the 00th pixel(upper left corner)
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u+pixel_delta_v);

    //render!
    std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n";
    for(int j=0;j<img_height;j++){
        std::clog<<"\rScanLines remaining : "<<(img_height-j)<<' '<<std::flush;
        for(int i=0;i<img_width;i++){
            auto pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

}
