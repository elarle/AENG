#ifndef AENG_MATH_H
#define AENG_MATH_H

#include "../utils/globals.h"

struct vec2;
struct vec3;
struct vec4;

struct mat4;

struct vec2{
    vec2();
    vec2(float x, float y);

    void print();
    
    int operator ==(const vec2 &a);
    int operator !=(const vec2 &a);

    vec2 operator +(const vec2 &a);
    vec2 operator -(const vec2 &a);
    vec2 operator *(const vec2 &a);
    vec2 operator /(const vec2 &a);

    float x;
    float y;
};

struct vec3{
    vec3();
    vec3(float x, float y, float z);

    void print();

    int operator ==(const vec3 &a);
    int operator !=(const vec3 &a);

    vec3 operator +(const vec3 &a);
    vec3 operator -(const vec3 &a);
    vec3 operator *(const vec3 &a);
    vec3 operator /(const vec3 &a);

    vec3 operator *(const float &a);

    void RAD_FIX();

    vec3 cross(const vec3 &a);
    vec3 inverse();
    vec3 normalize();

    float module();
    float dot(const vec3 &a);

    float x;
    float y;
    float z;
};

struct vec4{
    vec4();
    vec4(float x, float y, float z, float q);

    void print();

    int operator ==(const vec4 &a);
    int operator !=(const vec4 &a);

    vec4 operator +(const vec4 &a);
    vec4 operator -(const vec4 &a);
    vec4 operator *(const vec4 &a);
    vec4 operator /(const vec4 &a);

    vec4 cross(const vec4 &a);
    vec4 inverse();
    vec4 normalize();

    float module();
    float dot(const vec4 &a);

    float x;
    float y;
    float z;
    float q;
};

mat4 identity_m4();

struct mat4{

    mat4();
    mat4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33
    );

    float m[16];

    mat4 operator*(const mat4& rhs);
    mat4 operator*(const vec4& vec);

    void print();

};

inline float RAD_CORRECT(float ang){
    if(ang > PI){
        return -PI;
    }
    if(ang < -PI){
        return PI;
    }
    return ang;
}

inline void vec3::RAD_FIX(){
    this->x = RAD_CORRECT(this->x);
    this->y = RAD_CORRECT(this->y);
    this->z = RAD_CORRECT(this->z);
}

struct quat{
    quat();
    quat(float, float, float, float);
    quat(float, vec3);

    float x;
    float y;
    float z;
    float w;

    void print();
    void print(const char *);

    quat conjugate();

    quat operator*(const quat&);
    quat operator*(const vec3&);
};

#endif