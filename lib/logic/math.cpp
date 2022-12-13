#ifndef AENG_MATH
#define AENG_MATH

#include "math.hpp"
#include "../utils/console.hpp"
#include <cstdlib>

vec2::vec2(){}
vec2::vec2(float vx, float vy){
    x = vx;
    y = vy;
}
int vec2::operator==(const vec2 &a){
    if(this->x == a.x && this->y == a.y)return 1;
    return 0;
}
int vec2::operator!=(const vec2 &a){
    if(this->x == a.x && this->y == a.y)return 0;
    return 1;
}
vec2 vec2::operator-(const vec2 &a){
    return vec2(this->x-a.x, this->y-a.y);
}
vec3::vec3(){}
vec3::vec3(float vx, float vy, float vz){
    x = vx;
    y = vy;
    z = vz;
}

vec3 vec3::operator+(const vec3& v){
    vec3 r;
    r.x = x + v.x;
    r.y = y + v.y;
    r.z = z + v.z;
    return r;
}
vec3 vec3::operator-(const vec3& v){
    vec3 r;
    r.x = x - v.x;
    r.y = y - v.y;
    r.z = z - v.z;
    return r;
}
vec3 vec3::operator*(const float &a){
    vec3 r;
    r.x = x*a;
    r.y = y*a;
    r.z = z*a;
    return r;
}
vec3 vec3::operator*(const mat4 &a){
    vec3 r;
    r.x = (a.m[0]*x + a.m[4]*x + a.m[8]*x + a.m[12]*x);
    r.y = (a.m[1]*y + a.m[5]*y + a.m[9]*y + a.m[13]*y);
    r.z = (a.m[2]*z + a.m[6]*z + a.m[10]*z + a.m[14]*z);
    return r;
}
vec3 vec3::operator/(const float &a){
    vec3 r;
    x = x/a;
    y = y/a;
    z = z/a;
    return r;
}
vec3 vec3::operator+=(const mat4 &a){
    return vec3(0,0,0);
}
vec3 vec3::cross(const vec3 &a){
    vec3 r;
    r.x = y * a.z - z * a.y;
    r.y = z * a.x - x * a.z;
    r.z = x * a.y - y * a.x;
    return r;
}
vec3 vec3::normalize(){
    vec3 r;
    float len = sqrt(x*x + y*y + z*z);
    r.x = x/len;
    r.y = y/len;
    r.z = z/len;
    return r;
}
float vec3::dot(const vec3& a){
    vec3 r;
    r.x = x * a.x;
    r.y = y * a.y;
    r.z = z * a.z;
    return (r.x + r.y + r.z);
}
float vec3::module(){
    return sqrtf(x*x+y*y+z*z);
}
vec3 vec3::inverse(){
    return vec3(-x, -y, -z);
}
vec4::vec4(){}
vec4::vec4(float vx, float vy, float vz, float vw){
    x = vx;
    y = vy;
    z = vz;
    w = vw;
}
quat::quat(){}
quat::quat(float vx, float vy, float vz, float vw){
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

mat4 identity_mat4() { return mat4( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f ); }
mat4 zero_mat4() { return mat4( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f ); }

mat4 mat4::operator*( const mat4& rhs ) {
  mat4 r      = zero_mat4();
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
}
mat4 mat4::operator*( const vec4& vec ) {
  mat4 res = zero_mat4();
  res.m[0] = m[0] * vec.x; res.m[1] = m[1] * vec.x; res.m[2] = m[2] * vec.x; res.m[3] = m[3] * vec.x;
  res.m[4] = m[4] * vec.y; res.m[5] = m[5] * vec.y; res.m[6] = m[6] * vec.y; res.m[7] = m[7] * vec.y;
  res.m[8] = m[8] * vec.z; res.m[9] = m[9] * vec.z; res.m[10] = m[10] * vec.z; res.m[11] = m[11] * vec.z;
  res.m[12] = m[12] * vec.w; res.m[13] = m[13] * vec.w; res.m[14] = m[14] * vec.w; res.m[15] = m[15] * vec.w;
  return res;
}
void vec2::print(const char *color){
    printf("%s[%f, %f]\n", color, x, y);
}
void vec3::print(const char *color){
    printf("%s[%f, %f, %f]\n", color, x, y, z);
}
void vec4::print(const char *color){
    printf("%s[%f, %f, %f, %f]\n", color, x, y, z, w);
}
void mat4::print(const char * color){
    println(color,
    "[%f,%f,%f,%f] \n [%f,%f,%f,%f] \n [%f,%f,%f,%f] \n [%f,%f,%f,%f]",
        m[0], m[1], m[2], m[3],
        m[4], m[5], m[6], m[7],
        m[8], m[9], m[10], m[11],
        m[12], m[13], m[14], m[15]
    );
}

void translate( const vec2& v, float * pnt, int size){
    std::cout << *pnt;
}
void translate( const vec3& v, float * pnt){
    std::cout << *pnt;
}

mat4 translate( const mat4& m, const vec3& v){
    mat4 m_t = identity_mat4();
    m_t.m[12] = v.x;
    m_t.m[13] = v.y;
    m_t.m[14] = v.z;
    return m_t * m;
}

float random(float max){
    srand((unsigned int)time(NULL));
    return (float(rand())/float((max)) * max);
}

#endif