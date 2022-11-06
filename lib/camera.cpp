#ifndef AENG_CAMERA
#define AENG_CAMERA

#include "camera.hpp"
#include "math.cpp"
#include "math.hpp"
#include <cmath>

Camera::Camera(){}
void Camera::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}
void Camera::setRotation(float x, float y, float z){
    this->rotation.x = x*RAD;
    this->rotation.y = y*RAD;
    this->rotation.z = z*RAD;
}
void Camera::rotate(float x, float y, float z){
    this->rotation.x += x*RAD;
    this->rotation.y += y*RAD;
    this->rotation.z += z*RAD;
}
void Camera::setProjection(float fov, float aspect, float near, float far){
    this->projection.x = fov;
    this->projection.y = aspect;
    this->projection.z = near;
    this->projection.w = far;
}
void Camera::scale(float scale){
    this->s = scale;
}
mat4 Camera::getViewMatrix(){
    mat4 rxm = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos(rotation.x), sin(rotation.x), 0.0f,
        0.0f, -sin(rotation.x), cos(rotation.x), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 rym = mat4(
        cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin(rotation.y), 0.0f, cos(rotation.y), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 rzm = mat4(
        cos(rotation.z), sin(rotation.z), 0.0f, 0.0f,
        -sin(rotation.z), cos(rotation.z), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    
    return rxm * rym * rzm;
}
mat4 Camera::getProjMatrix(){
    return mat4(
        1.0f / tan(projection.x * 0.5f) / projection.y, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f / tan(projection.x * 0.5f), 0.0f, 0.0f,
        0.0f, 0.0f, -(projection.w + projection.z) / (projection.w - projection.z), -1.0f,
        0.0f, 0.0f, -(2.0f * projection.w * projection.z) / (projection.w - projection.z), 0.0f
    );
}
mat4 Camera::getDefaultProj(){
    return mat4(
        s, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, s, 0.0,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}
/*
float * Camera::getProj_matrix(){
    float i_r = 1.0f / tan( projection.x * 0.5f );
    float Sx = i_r / aspect;
    float Sy = i_r;
    float Sz = -( far + near ) / ( far - near);
    float Pz = -( 2.0f * far * near ) / ( far - near);
    float proj_matrix[] = {
        Sx, 0.0f, 0.0f, 0.0f,
        Sy, 0.0f, 0.0f, 0.0f,
        Sz, -1.0f, 0.0f, 0.0f, Pz
    };
    return proj_matrix;
}
*/
#endif