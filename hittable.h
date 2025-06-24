#ifndef HITTABLE_H
#define HITTABLE_H
//#include<ray.h>
class hit_record{
    public:
        point3 p;
        double t;
        vec3 normal;
        //this bool value is true if the ray is outside the surface
        //using this you can always know if the ray is hitting from outside or inside!
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal){
            front_face = dot(r.direction(), outward_normal) < 0;
            //we are keeping the normal always against the incident ray
            normal = front_face?outward_normal:-outward_normal;
        }

};

class hittable{
    public:
        virtual ~hittable() = default;
        //t being the scaling factor as in A + tB = P(t). hence t_min is the min acceptable t 
        //to count as a hit and t_max being the max acceptable t to count as a hit
        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};
#endif
