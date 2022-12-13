#ifndef AENG_CAMERA
#define AENG_CAMERA

#include "camera.hpp"
#include "../logic/math.cpp"
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
    this->rotation_r.x = x;
    this->rotation_r.y = y;
    this->rotation_r.z = z;
}
void Camera::move(int dir_n, float vel){


    this->speed = vel;

    vec3 nc;

    if(dir_n == 1){
        //Calculate W movement (fwd) "pos 0º"
        this->position = this->position+(
            vec3(
                (this->rotation.y/M_PY)*M_PY, 
                (-this->rotation.x/M_PY)*M_PY, 
                (this->rotation.z/M_PY)*M_PY)
            ).normalize()*this->speed;
        this->position.print(GREEN);
    }
    if(dir_n == 2){
        this->position = this->position+(
            vec3(
                (this->rotation.x/M_PY)*M_PY, 
                (this->rotation.y/M_PY)*M_PY, 
                (this->rotation.z/M_PY)*M_PY)
            ).normalize()*this->speed;
        this->position.print(GREEN);
    }
    if(dir_n == 3){
    }
    if(dir_n == 4){
    }
}
void Camera::moveV2(int dir_n, float vel){

    this->speed = vel;

    float t = 0;
    float t2 = 0;

    if(dir_n == 1){
        t = -90*RAD;
        t2 = -90*RAD;
    }
    if(dir_n == 2){
        t = -270*RAD;
        t2 = -90*RAD;
    }
    if(dir_n == 3){
        t = -90*RAD;
    }
    if(dir_n == 4){
        t = -90*RAD;
        t2 = 180*RAD;
    }

    vec3 dir = vec3(
        sinf(rotation.x+t)*cosf(-rotation.y+t2),
        cosf(-rotation.x+t),
        sinf(rotation.x+t)*sinf(-rotation.y+t2)
    );

    dir.print(BLUE);

    dir=dir*speed;

    dir.print(MAGENTA);

    if(dir_n != 0)this->position = this->position + dir;

}
void Camera::rotate(float x, float y, float z){
    this->rotation.x += x*RAD;
    this->rotation.y += y*RAD;
    this->rotation.z += z*RAD;
    this->rotation_r.x += x;
    this->rotation_r.y += y;
    this->rotation_r.z += z;

    /*
    
    if(this->rotation.x > M_PI)rotation.x = -M_PI;
    if(this->rotation.x < -M_PI)rotation.x = M_PI;

    if(this->rotation.y > M_PI)rotation.y = -M_PI;
    if(this->rotation.y < -M_PI)rotation.y = M_PI;

    if(this->rotation.z > M_PI)rotation.z = -M_PI;
    if(this->rotation.z < -M_PI)rotation.z = M_PI;

    */
}
void Camera::setProjection(float fov, float aspect, float near, float far){
    this->projection.x = fov;
    this->projection.y = aspect;
    this->projection.z = near;
    this->projection.w = far;
}
void Camera::scale(float scale){
    this->s += scale;
}

mat4 Camera::getViewMatrix(){

    mat4 sc = mat4(
        this->s, 0, 0, 0,
        0, this->s, 0, 0,
        0, 0, this->s, 0,
        0, 0, 0, 1
    );
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
    mat4 tf = mat4(
        1.0f, 0.0f, 0.0f, -position.x,
        0.0f, 1.0f, 0.0f, -position.y,
        0.0f, 0.0f, 1.0f, -position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    return sc * (rzm * rym * rxm) * tf;
}
mat4 Camera::getViewMatrixV2(){
    /*
    vec3 Z = (this->pposition - this->position).normalize();
    vec3 X = dest.cross(Z).normalize();
    vec3 Y = Z.cross(X).normalize();
    mat4 view = mat4(
        X.x, Y.x, Z.x, 0,
        X.y, Y.y, Z.y, 0,
        X.z, Y.z, Z.z, 0,
        -position.dot(X), -position.dot(Y), -position.dot(Z), 1
    );
    return view;
    */

    mat4 tf = mat4(
        1.0f, 0.0f, 0.0f, pposition.x-position.x,
        0.0f, 1.0f, 0.0f, pposition.y-position.y,
        0.0f, 0.0f, 1.0f, pposition.z-position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

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

    ((rxm * rym * rzm) * tf).print(GREEN);
    vec3 tp = pposition*((rxm * rym * rzm) * tf);
    tp.print(BLUE);

    vec3 Z = (tp - this->position).normalize();
    vec3 X = dest.cross(Z).normalize();
    vec3 Y = Z.cross(X).normalize();
    
    mat4 view = mat4(
        X.x, Y.x, Z.x, 0.0f,
        X.y, Y.y,Z.y, 0.0f,
        X.z, Y.z, Z.z, 0.0f,
        -position.dot(X), -position.dot(Y), -position.dot(Z), 1.0f
    );
    return view;
}
mat4 Camera::getViewMatrixV3(){
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
    mat4 tf = mat4(
        1.0f, 0.0f, 0.0f, -position.x,
        0.0f, 1.0f, 0.0f, -position.y,
        0.0f, 0.0f, 1.0f, -position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    return tf * (rzm * rym * rxm);
}
mat4 Camera::getProjMatrix(){
    float fov_rad = projection.x*RAD;
    float i = 1.0f / tan(fov_rad/2.0f);
    mat4 proj = zero_mat4();
    proj.m[0] = i/(projection.y);
    proj.m[5] = i;
    proj.m[11] = -1.0f;
    /*
    proj.m[10] = -(1000.0f + 1.0f)/(1000.0f - 1.0f);
    proj.m[14] = -(2.0f*1.0f*1000.0f)/(1.0f - 1000.0f);
    */

    float near = projection.z;
    float far = projection.w;

    proj.m[10] = -(far + near)/(far - near);
    proj.m[14] = -(2.0f*near*far)/(near - far);

    return proj;
}
#endif