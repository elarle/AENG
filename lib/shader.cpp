#ifndef AENG_SHADER
#define AENG_SHADER

#include "shader.hpp"
#include "reader.h"
#include "util.h"
#include <GL/eglew.h>
#include <GL/gl.h>

GLuint createVS();
inline GLuint createVS(){
    const char* p;
    char VS[MAX_SHADER_SIZE];
    readfile("./shaders/VS.glsl", VS);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    p = (const GLchar*)VS;
    glShaderSource(vs, 1, &p, NULL);
    glCompileShader(vs);
    return vs;
}
GLuint createFS();
inline GLuint createFS(){
    const char* p;
    char FS[MAX_SHADER_SIZE];
    readfile("./shaders/FS.glsl", FS);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    p = (const GLchar*)FS;
    glShaderSource(fs, 1, &p, NULL);
    glCompileShader(fs);
    return fs;
}
void err_cb(int err, const char* err_msg);
inline void err_cb(int err, const char* err_msg){
    log(LOG_ERROR, "GLFW ERROR: %s", err_msg);
}
void shader_info_log(GLuint shader, int type);
void shader_program_log(GLuint shader_program);
inline void shader_info_log(GLuint shader, int type){
    int al = 0;
    char info_log[MAX_SHADER_LOG_SIZE];
    glGetShaderInfoLog(shader, MAX_SHADER_LOG_SIZE, &al, info_log);
    if(al > 0 && type == 0){
        log(LOG_WARNING, "Vertex Shader Log:\n\t%s", info_log);
    }
    if(al > 0 && type == 1){
        log(LOG_WARNING, "Fragment Shader Log:\n\t%s", info_log);
    }
}
inline void shader_program_log(GLuint shader_program){
    int al = 0;
    char info_log[MAX_SHADER_LOG_SIZE];
    glGetProgramInfoLog(shader_program, MAX_SHADER_LOG_SIZE, &al, info_log);
    if(al > 0){
        log(LOG_WARNING, "Shader Program Info Log:\n\t%s", info_log);
    }
}
int is_valid(GLuint sp);
inline int is_valid(GLuint sp){
    int params = -1;
    glValidateProgram(sp);
    glGetProgramiv(sp, GL_VALIDATE_STATUS, &params);
    if(params != GL_TRUE){
        shader_program_log(sp);
        return 0;
    }
    return 1;
}
void point_vbo(GLuint*PVBO, int size, float* mesh);
inline void point_vbo(GLuint *PVBO, int size, float* mesh){
    glGenBuffers(1, PVBO);
    glBindBuffer(GL_ARRAY_BUFFER , *PVBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), mesh, GL_STATIC_DRAW);    
    log(LOG_INFO, "Created Point vertex buffer object");
}
void color_vb0(GLuint*PVBO, int size, float* mesh);
inline void color_vbo(GLuint*CVBO, int size, float* colors){
    glGenBuffers(1, CVBO);
    glBindBuffer(GL_ARRAY_BUFFER , *CVBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), colors, GL_STATIC_DRAW);    
    log(LOG_INFO, "Created Color vertex buffer object");
}

#endif