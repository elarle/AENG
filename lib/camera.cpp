#ifndef AENG_CAMERA
#define AENG_CAMERA

#include "camera.hpp"
#include "math.cpp"
#include "math.hpp"

Camera::Camera(){}
void Camera::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}
void Camera::setRotation(float x, float y, float z){
    this->rotation.x = x;
    this->rotation.y = y;
    this->rotation.z = z;
}
void Camera::setProjection(float fov, float aspect, float near, float far){
    this->projection.x = fov;
    this->projection.y = aspect;
    this->projection.z = near;
    this->projection.w = far;
}
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

#endif