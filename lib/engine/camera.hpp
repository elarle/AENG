#ifndef CAMERA_H
#define CAMERA_H
#include "../logic/math.cpp"
#include "../logic/math.hpp"

struct Camera;
struct Camera {
    Camera();
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);

    void move(int dir, float vel);
    void moveV2(int dir, float vel);
    void rotate(float x, float y, float z);

    void setProjection(float fov, float aspect, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top);
    void setViewport(float x, float y, float width, float height);

    void scale(float scale);

    void lookAt(vec3 pos);

    mat4 getViewMatrix();
    mat4 getViewMatrixV2();
    mat4 getViewMatrixV3();
    mat4 getProjMatrix();
    mat4 getDefaultProj();

	vec3 position = vec3(0.0f, 0.0f, 0.0f);

    vec3 pposition = vec3(0.0f,0.0f,0.0f);
    
    vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
    vec3 rotation_r = vec3(0.0f, 0.0f, 0.0f);
    
    vec3 dest = vec3(0.0f, 1.0f, 0.0f);

    vec4 projection = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    float speed = 0.0f;
    float yaw_speed = 10.0f;

    float yrot = 0.0f;

    float s = 1.0f;
};

#endif