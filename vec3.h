#ifndef VEC3_H
#define VEC3_H

//#include<cmath>
//#include<iostream>

class vec3{
   public:
       double e[3]; //array to store vector components

       //member initializer lists 

       vec3()   
           : e{0,0,0} {}

       vec3(double e0, double e1,double e2) 
           : e{e0, e1, e2} {}

       //member functions to get the coordinates of vector: 

       double x() const { return e[0]; }
       double y() const { return e[1]; }
       double z() const { return e[2]; }

       //operators:
       friend vec3 operator+(const vec3& v1,const vec3& v2);

       friend vec3 operator-(const vec3& v1,const vec3& v2);

       friend vec3 operator*(const vec3& v, double t);
       friend vec3 operator*(double t, const vec3& v);

       friend vec3 operator/(const vec3& v, double t);

       vec3 operator-() const{
           return vec3(-e[0], -e[1], -e[2]);
       }
       double operator[](int i) const{
           return e[i];
       }
       double& operator[](int i){
           return e[i];
       }

       vec3& operator+=(const vec3& v) {
           e[0] += v.e[0];
           e[1] += v.e[1];
           e[2] += v.e[2];
           return *this;
       }
        
       vec3& operator*=(double t) {
           e[0] *= t;
           e[1] *= t;
           e[2] *= t;
           return *this;
       }

       vec3& operator/=(double t) {
           return *this *= 1/t;
       }

       //some useful member functions:
       static vec3 random(){
            return vec3(random_double(), random_double(), random_double());
       }
       static vec3 random(double min, double max){
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
       }
       double length_squared() const{
           return (e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
       }

       double length() const{
           return std::sqrt(length_squared());
       }
    
       vec3 unit() const{
           return *this/length();
       }

       friend double dot(const vec3& v1, const vec3& v2);
       friend vec3 cross(const vec3& v1, const vec3& v2);

       //friend vec3 reflect (const vec3& v, const vec3& normal);
       //n1-> r_index of incident medium , n2-> .. of refracted medium
       //friend vec3 refract (const vec3& v, const vec3& normal, float n1 , float n2);

       //to take care of situations in which the vec3 is near zero (may become zero due to floating pt)
       //that may lead to inf or nan if you divide by that or something!
       bool near_zero() const
       {
           // Return true if the vector is close to zero in all dimensions.
           auto s = 1e-8;
           return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
       }
};

inline vec3 random_unit_vector()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}
//helps clarify the geometric difference between the two 
using point3 = vec3;

vec3 operator+(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);
}

vec3 operator-(const vec3& v1, const vec3& v2){
    return vec3(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);
}
vec3 operator*(const vec3& v, double t){
    return vec3(v.e[0]*t,v.e[1]*t,v.e[2]*t);
}
vec3 operator*(double t, const vec3& v){
    return vec3(v.e[0]*t,v.e[1]*t,v.e[2]*t);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator/(const vec3& v, double t){
    return vec3(v.e[0]/t,v.e[1]/t,v.e[2]/t);
}

double dot(const vec3& v1, const vec3& v2) {
    return ((v1.e[0]*v2.e[0])+(v1.e[1]*v2.e[1])+(v1.e[2]*v2.e[2]));
}

vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
            v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
            v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}
//all incident vec and normal vectors and returned vectors are normalized
inline vec3 reflect (const vec3& v, const vec3& normal){
    return v - (2*dot(v, normal))*normal;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
#endif
