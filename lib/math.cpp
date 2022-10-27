#ifndef AENG_MATH
#define AENG_MATH

#include "math.hpp"
#include <iostream>

vec2::vec2(){}
vec2::vec2(float vx, float vy){
    x = vx;
    y = vy;
}
vec3::vec3(){}
vec3::vec3(float vx, float vy, float vz){
    x = vx;
    y = vy;
    z = vz;
}
vec4::vec4(){}
vec4::vec4(float vx, float vy, float vz, float vw){
    x = vx;
    y = vy;
    z = vz;
    w = vw;
}
mat4::mat4(){}
mat4::mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33){
    m[0] = m00;
    m[1] = m01;
    m[2] = m02;
    m[3] = m03;
    m[4] = m10;
    m[5] = m11;
    m[6] = m12;
    m[7] = m13;
    m[8] = m20;
    m[9] = m21;
    m[10] = m22;
    m[11] = m23;
    m[12] = m30;
    m[13] = m31;
    m[14] = m32;
    m[15] = m33;
}
void translate( const vec2& v, float * pnt, int size){
    std::cout << *pnt;
}
void translate( const vec3& v, float * pnt){
    std::cout << *pnt;
}
#endif