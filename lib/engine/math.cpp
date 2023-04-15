#ifndef AENG_MATH
#define AENG_MATH

#include <math.h>
#include "math.h"
#include "../utils/console.h"

vec2::vec2(){
    this->x = 0; this->y = 0;
}
vec3::vec3(){
    this->x = 0; this->y = 0; this->z = 0;
}
vec4::vec4(){
    this->x = 0; this->y = 0; this->z = 0; this->q = 0;
}

vec2::vec2(float x, float y){
    this->x = x; this->y = y;
}
vec3::vec3(float x, float y, float z){
    this->x = x; this->y = y; this->z = z;
}
vec4::vec4(float x, float y, float z, float q){
    this->x = x; this->y = y; this->z = z; this->q = q;
}

mat4::mat4(){
    for(int i = 0; i < 16; i++){
        this->m[i] = 0;
    }
}

mat4::mat4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
){
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


//-----------COMPARATORS-----------//

// VEC2

int vec2::operator==(const vec2 &a){
    return (a.x == this->x && a.y == this->y) ? 1 : 0;
}

int vec2::operator!=(const vec2 &a){
    return (a.x == this->x && a.y == this->y) ? 0 : 1;
}

// VEC3

int vec3::operator==(const vec3 &a){
    return (a.x == this->x && a.y == this->y && a.z == this->z) ? 1 : 0;
}

int vec3::operator!=(const vec3 &a){
    return (a.x == this->x && a.y == this->y && a.z == this->z) ? 0 : 1;
}

// VEC 4

int vec4::operator==(const vec4 &a){
    return (a.x == this->x && a.y == this->y && a.z == this->z && a.q == this->q) ? 1 : 0;
}

int vec4::operator!=(const vec4 &a){
    return (a.x == this->x && a.y == this->y && a.z == this->z && a.q == this->q) ? 0 : 1;
}

//-----------OPERATORS-----------//

// VEC2

vec2 vec2::operator+(const vec2 &a){
    return vec2(this->x+a.x, this->y+a.y);
}

vec2 vec2::operator-(const vec2 &a){
    return vec2(this->x-a.x, this->y-a.y);
}

vec2 vec2::operator*(const vec2 &a){
    return vec2(this->x*a.x, this->y*a.y);
}

vec2 vec2::operator/(const vec2 &a){
    return vec2(this->x/a.x, this->y/a.y);
}

// VEC3

vec3 vec3::operator+(const vec3 &a){
    return vec3(this->x+a.x, this->y+a.y, this->z+a.z);
}

vec3 vec3::operator-(const vec3 &a){
    return vec3(this->x-a.x, this->y-a.y, this->z-a.z);
}

vec3 vec3::operator*(const vec3 &a){
    return vec3(this->x*a.x, this->y*a.y, this->z*a.z);
}

vec3 vec3::operator*(const float &a){
    return vec3(this->x*a, this->y*a, this->z*a);
}

vec3 vec3::operator/(const vec3 &a){
    return vec3(this->x/a.x, this->y/a.y, this->z/a.z);
}

// VEC 4

vec4 vec4::operator+(const vec4 &a){
    return vec4(this->x+a.x, this->y+a.y, this->z+a.z, this->q+a.q);
}

vec4 vec4::operator-(const vec4 &a){
    return vec4(this->x-a.x, this->y-a.y, this->z-a.z, this->q+a.q);
}

vec4 vec4::operator*(const vec4 &a){
    return vec4(this->x*a.x, this->y*a.y, this->z*a.z, this->q*a.q);
}

vec4 vec4::operator/(const vec4 &a){
    return vec4(this->x/a.x, this->y/a.y, this->z/a.z, this->q/a.q);
}

//---------PRODUCTS---------//

// VEC 3

vec3 vec3::cross(const vec3 &a){
    return vec3(
        this->y*a.z - this->z*a.y,
        this->z*a.x - this->x*a.z,
        this->x*a.y - this->y*a.x
    );
}

vec3 vec3::normalize(){
    float b = sqrtf(x*x + y*y + z*z);
    return vec3(
        this->x/b,
        this->y/b,
        this->z/b
    );
}

float vec3::dot(const vec3& a){
    return (this->x*a.x + this->y*a.y + this->z*a.z);
}

float vec3::module(){
    return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}

vec3 vec3::inverse(){
    return vec3(this->z, this-> y, this->x);
}

//VEC 4

vec4 vec4::normalize(){
    float b = sqrtf(x*x + y*y + z*z + q*q);
    return vec4(
        this->x/b,
        this->y/b,
        this->z/b,
        this->q/b
    );
}

float vec4::dot(const vec4& a){
    return (this->x*a.x + this->y*a.y + this->z*a.z);
}

float vec4::module(){
    return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z  + this->q*this->q);
}

//MAT4

mat4 identity(){
    return mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

mat4 mat4::operator*(const mat4& rhs){
    mat4 r = mat4();
    int r_index = 0;
    for ( int col = 0; col < 4; col++ ) {
        for ( int row = 0; row < 4; row++ ) {
            float sum = 0.0f;
            for ( int i = 0; i < 4; i++ ) { sum += rhs.m[i + col * 4] * m[row + i * 4]; }
            r.m[r_index] = sum;
            r_index++;
        }
    }
    return r;
};

mat4 mat4::operator*( const vec4& vec ) {
  mat4 res = mat4();
  res.m[0] = m[0] * vec.x; res.m[1] = m[1] * vec.x; res.m[2] = m[2] * vec.x; res.m[3] = m[3] * vec.x;
  res.m[4] = m[4] * vec.y; res.m[5] = m[5] * vec.y; res.m[6] = m[6] * vec.y; res.m[7] = m[7] * vec.y;
  res.m[8] = m[8] * vec.z; res.m[9] = m[9] * vec.z; res.m[10] = m[10] * vec.z; res.m[11] = m[11] * vec.z;
  res.m[12] = m[12] * vec.q; res.m[13] = m[13] * vec.q; res.m[14] = m[14] * vec.q; res.m[15] = m[15] * vec.q;
  return res;
}

// PRINTS

void vec2::print(){
    println(WHITE ,"[%f, %f]\n", x, y);
}
void vec3::print(){
    println(WHITE ,"[%f, %f, %f]\n", x, y, z);
}
void vec4::print(){
    println(WHITE ,"[%f, %f, %f, %f]\n", x, y, z, q);
}
void mat4::print(){
    println(WHITE,
    "[%f,%f,%f,%f] \n [%f,%f,%f,%f] \n [%f,%f,%f,%f] \n [%f,%f,%f,%f]",
        m[0], m[1], m[2], m[3],
        m[4], m[5], m[6], m[7],
        m[8], m[9], m[10], m[11],
        m[12], m[13], m[14], m[15]
    );
}

mat4 traslate( const mat4& m, const vec3& v){
    mat4 m_t = identity();
    m_t.m[12] = v.x;
    m_t.m[13] = v.y;
    m_t.m[14] = v.z;
    return m_t * m;
}

float random(float max){
    srand((unsigned int)time(NULL));
    return (float(rand())/float((max)) * max);
}

//-------------------------//

quat::quat(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

quat::quat(float W, float X, float Y, float Z){
    this->x = X;
    this->y = Y;
    this->z = Z;
    this->w = W;
}

quat::quat(float W, vec3 vec){
    this->w = W;
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
}

quat quat::conjugate(){
    return quat(this->w, -this->x, -this->y, -this->z);
}

quat quat::operator*(const quat &q){
    return quat(
        (w*q.w)-(x*q.x)-(y*q.y)-(z*q.z),
        (x*q.w)+(w*q.x)+(y*q.z)-(z*q.y),
        (y*q.w)+(w*q.y)+(z*q.x)-(x*q.z),
        (z*q.w)+(w*q.z)+(x*q.y)-(y*q.x)
    );
}

quat quat::operator*(const vec3 &v){
    float w = - (x*v.x) - (y * v.y) - (z * v.z);
    return quat(
        w,
        (w*v.x)+(y*v.z)-(z*v.y),
        (w*v.y)+(z*v.x)-(x*v.z),
        (w*v.z)+(x*v.y)-(y*v.x)
    );
}

void quat::print(){
    println(BLUE ,"Q[%f, %f, %f, %f]\n", x, y, z, w);
}

void quat::print(const char * name){
    println(BLUE ,"%s:(%f, %f, %f, %f)", name, x, y, z, w);
}

#endif