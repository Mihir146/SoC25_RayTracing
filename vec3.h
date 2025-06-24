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

       friend vec3 reflect (const vec3& v, const vec3& normal);
       //n1-> r_index of incident medium , n2-> .. of refracted medium
       friend vec3 refract (const vec3& v, const vec3& normal, float n1 , float n2);
};
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
vec3 reflect (const vec3& v, const vec3& normal){
    vec3 reflected_ray = v.unit() - (2*dot(v.unit(), normal.unit())*normal.unit());
    return reflected_ray;
}

vec3 refract (const vec3& v, const vec3& normal, double n1, double n2){ //n1-> r_index of incident medium , n2-> .. of refracted medium eta->n1/n2
    auto eta = n1/n2;
    auto cos_thetaI =  -dot(v.unit(), normal.unit());
    auto sin_thetaT_sqr = eta*eta*(1.0-cos_thetaI*cos_thetaI);
    auto cos_thetaT = std::sqrt(1.0 - sin_thetaT_sqr);
    vec3 refracted_ray = eta*v + (eta*cos_thetaI - cos_thetaT)*normal.unit();
    if(sin_thetaT_sqr > 1.0){
        return reflect(v, normal);
    } 
    return refracted_ray.unit();
}

#endif
