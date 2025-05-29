#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

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
       vec3 operator+(const vec3& other){
           return vec3(e[0]+other.e[0], e[1]+other.e[1],e[2]+other.e[2]);
       }
       
       vec3 operator-(const vec3& other){
           return vec3(e[0]-other.e[0], e[1]-other.e[1],e[2]-other.e[2]);
       }

       vec3 operator*(double t){
           return vec3(e[0]*t, e[1]*t, e[2]*t);
       }

       vec3 operator/(double t){
           return vec3(e[0]/t, e[1]/t, e[2]/t);
       }

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
       double length_squared(){
           return (e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
       }

       double length(){
           return std::sqrt(length_squared());
       }
    
       vec3 unit(){
           //double len = length();
           //vec3 unit_vec = vec3();
           //unit_vec[0] = e[0]/len;
           //unit_vec[1] = e[1]/len;
           //unit_vec[2] = e[2]/len;
           //return unit_vec;
           return *this/length();
       }

       double dot(const vec3& other){
           return ((e[0]*other.e[0])+(e[1]*other.e[1])+(e[2]*other.e[2]));
       }

       vec3 cross(const vec3& other){
           return vec3(e[1] * other.e[2] - e[2] * other.e[1],
                   e[2] * other.e[0] - e[0] * other.e[2],
                   e[0] * other.e[1] - e[1] * other.e[0]);
       }

};


#endif
