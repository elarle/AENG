#ifndef AENG_OBJECT
#define AENG_OBJECT

#include "material.h"
#include "mesh.h"
#include "shader.cpp"
#include "../engine/math.h"

class object{

    public:
    object();

    mesh malla;
    material texture;

    GLuint VB;
    GLuint UB;
    GLuint NB;
    GLuint VA;

    int load();

    int load_file(const char * file);
    int load_shaders(const char * vs, const char * fs);

    vec3 position = vec3(0.0f, 0.0f, 0.0f);
    vec3 rotation = vec3(0.0f, 0.0f, 0.0f);
    vec3 scale = vec3(1.0f, 1.0f, 1.0f);

    void move(vec2);
    void rotate(vec3);

    mat4 matrix;
    void update_matrix();

    void pre_draw();

    void free();

    bool phisics = 0;
};

#endif