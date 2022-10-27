#ifndef CAMERA_H
#define CAMERA_H
#include "math.cpp"
#include "math.hpp"

struct Camera;
struct Camera {
    Camera();
    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setProjection(float fov, float aspect, float near, float far);
    void setPerspective(float fov, float aspect, float near, float far);
    void setOrthographic(float left, float right, float bottom, float top);
    void setViewport(float x, float y, float width, float height);
    mat4 getViewMatrix();
	vec3 position = vec3(0.0f, 0.0f, 0.0f);
    vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
    vec4 projection = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec2 viewport = vec2(0.0f, 0.0);
	float fov;
	float aspect;
	float near;
	float far;
    float * getProj_matrix();
};

#endif