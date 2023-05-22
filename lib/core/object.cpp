#ifndef AENG_OBJECT_FUNCTIONS
#define AENG_OBJECT_FUNCTIONS

#include "object.h"
#include "../engine/math.cpp"
#include "material.h"
#include "../utils/lgl.h"

object::object(){
    this->matrix = identity();
}

int object::load_file(const char *file){
    return malla.load_file(file);
}
int object::load_shaders(const char * vs, const char * fs){
    int i = 0;
    return i;
}
int object::load(){

    glGenVertexArrays(1, &VA);

    glBindVertexArray(VA);

    glGenBuffers(1, &VB);
    glGenBuffers(1, &UB);
    glGenBuffers(1, &NB);

    glBindBuffer(GL_ARRAY_BUFFER, VB);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBufferData(GL_ARRAY_BUFFER, malla.SIZE * sizeof(float), malla.heap_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, NB);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBufferData(GL_ARRAY_BUFFER, malla.SIZE * sizeof(float), malla.heap_normals, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, UB);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glBufferData(GL_ARRAY_BUFFER, malla.UVS * sizeof(float), malla.heap_uvs, GL_STATIC_DRAW);

    return 0;
}

void object::pre_draw(){

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.IMG_ID);

}

void object::update_matrix(){
    matrix = matrix * vec4(
        scale.x,
        scale.y,
        scale.z,
        1.0f
    );
    matrix = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos(rotation.x), sin(rotation.x), 0.0f,
        0.0f, -sin(rotation.x), cos(rotation.x), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    //ROT Y
    matrix = matrix * mat4(
        cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin(rotation.y), 0.0f, cos(rotation.y), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    //ROT Z
    matrix = matrix * mat4(
        cos(rotation.z), sin(rotation.z), 0.0f, 0.0f,
        -sin(rotation.z), cos(rotation.z), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    //TRANSLATE
    matrix = matrix * mat4(
        1.0f, 0.0f, 0.0f, position.x,
        0.0f, 1.0f, 0.0f, position.y,
        0.0f, 0.0f, 1.0f, position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

}

void object::move(vec2 dir){
    float t = (dir.x * 90.0f)*RAD;
    float t2 = (90.0f + (dir.y * 90.0f))*RAD;

    vec3 dirv = vec3(
        sinf(rotation.x+t)*cosf(-rotation.y+t2),
        cosf(-rotation.x+t),
        sinf(rotation.x+t)*sinf(-rotation.y+t2)
    );

    position = position + (dirv*0.005);
    update_matrix();
}

void object::rotate(vec3 dir){
    rotation = rotation + dir;
    update_matrix();
}

void object::free(){
    delete malla.heap_normals;
    delete malla.heap_uvs;
    delete malla.heap_vertices;
}

#endif