#ifndef AENG_MATH_H
#define AENG_MATH_H

#include <math.h>

#define M_PY 3.141592653589793238462

#define RAD (2.0 * M_PY) / 360.0
#define DEG 360.0 / (2.0 * M_PY)

struct vec2;
struct vec3;
struct vec4;

struct mat4;

struct quat;

struct vec2 {
    vec2();
    vec2(float x, float y);
    void print(const char * color);
    int operator==(const vec2 &a);
    int operator!=(const vec2 &a);
    vec2 operator-(const vec2 &a);
    float t_arr();
    float x;
    float y;
};
struct vec3 {
    vec3();
    vec3(float x, float y, float z);
    vec3 operator+(const vec3& a);
    vec3 operator-(const vec3& a);
    vec3 operator*(const mat4& a);
    vec3 operator*(const float& a);
    vec3 operator+=(const mat4& a);
    vec3 operator/(const float& a);
    vec3 cross(const vec3& a);
    vec3 inverse();
    vec3 normalize();
    float module();
    void print(const char * color);
    float dot(const vec3& a);
    float t_arr();
    float x;
    float y;
    float z;
};

struct vec4 {
    vec4();
    vec4(float x, float y, float z, float w);
    void print(const char * color);
    float t_arr();
    float x;
    float y;
    float z;
    float w;
};

struct mat4 {
    mat4();
    mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);
    float m[16];
    mat4 operator*( const mat4& rhs );
    mat4 operator*( const vec4& vec);
    void print(const char* color);
};

struct quat {
    quat();
    quat(float x, float y, float z, float w);
    float x;
    float y;
    float z;
    float w;
};

struct vec2 operator+(vec2 a, vec2 b);
struct vec2 operator*(vec2 a, float b);
struct vec2 operator/(float b, vec2 a);

float random(float max, float min);

#endif