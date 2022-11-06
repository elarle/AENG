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
    x = -vx;
    y = -vy;
    z = -vz;
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
mat4 perspective( float fovy, float aspect, float near, float far ) {
  float fov_rad       = fovy * RAD;
  float inverse_range = 1.0f / tan( fov_rad / 2.0f );
  float sx            = inverse_range / aspect;
  float sy            = inverse_range;
  float sz            = -( far + near ) / ( far - near );
  float pz            = -( 2.0f * far * near ) / ( far - near );
  mat4 m              = zero_mat4(); // make sure bottom-right corner is zero
  m.m[0]              = sx;
  m.m[5]              = sy;
  m.m[10]             = sz;
  m.m[14]             = pz;
  m.m[11]             = -1.0f;
  return m;
}


#endif