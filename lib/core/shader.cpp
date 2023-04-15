#ifndef AENG_SHADER
#define AENG_SHADER

#include "../utils/globals.h"
#include "../utils/reader.h"
#include <GL/eglew.h>
#include <GL/gl.h>
#include "shader.h"

shader::shader(){}

inline void shader_info(GLuint shader){
    int al = 0;
    char info_log[MAX_SHADER_LOG_SIZE];
    glGetShaderInfoLog(shader, MAX_SHADER_LOG_SIZE, &al, info_log);
    if(al > 0){
        log(LOG_WARNING, "Vertex Shader Log:\n\t%s", info_log);
    }
}

int is_valid(GLuint sp){
    int params = -1;
    glValidateProgram(sp);
    glGetProgramiv(sp, GL_VALIDATE_STATUS, &params);
    if(params != GL_TRUE){
        shader_info(sp);
        log(LOG_WARNING, "ERROR COMPILING SHADER: %i", params);
        return 0;
    }
    return 1;
};

inline void load_s(GLuint *so, const char * file){
    const char*p;
    char s[MAX_SHADER_SIZE];
    readfile(file, s);
    p = (const GLchar* )s;
    glShaderSource(*so, 1, &p, NULL);
    glCompileShader(*so);
    log(LOG_INFO, "Loading shader (%s)", file);
};

/* int shader::load_data(int p_size, float * p, int m_size, float * m){
    glGenVertexArrays(2, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &point_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, point_vbo);
    glBufferData(GL_ARRAY_BUFFER, p_size*sizeof(float), p, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normal_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
    glBufferData(GL_ARRAY_BUFFER, p_size*sizeof(float), p, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    return 0;
}; */

int shader::load(const char * vs, const char * fs){
    VS_FILE = vs; FS_FILE = fs;

    if(!VS_FILE || !FS_FILE)return 1;

    this->vertex = glCreateShader(GL_VERTEX_SHADER);
    this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

    load_s(&vertex, VS_FILE);
    load_s(&fragment, FS_FILE);

    log(LOG_INFO, "Loaded shaders");

    program = glCreateProgram();
    glAttachShader(program, this->vertex);
    glAttachShader(program, this->fragment);

    glBindAttribLocation(program, 0, "vertex_position");
    glBindAttribLocation(program, 1, "vertex_texture");

    glLinkProgram(program);

    if(!is_valid(program)){
        log(LOG_ERROR, "Shader creation failed");
        return 1;
    }

    return 0;
};

#endif