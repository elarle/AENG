#ifndef AENG_UTILS
#define AENG_UTILS

#include "../logic/math.hpp"
#include <GL/eglew.h>
#include <GL/gl.h>
#include "../engine/shader.cpp"


int *mmlp;
int *vmlp;
int *pmlp;

void create_shaders(GLuint *shader_program, GLuint *vs, GLuint *fs, GLuint *PVBO, GLuint *MVBO, GLuint *VAO){
    *vs = createVS();
    log(LOG_INFO, "Loaded Vertex Shader");
    *fs = createFS();
    log(LOG_INFO, "Loaded Fragment Shader");

    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *PVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, *MVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    log(LOG_INFO, "Generated VAO");

    *shader_program = glCreateProgram();
    glAttachShader(*shader_program, *fs);
    glAttachShader(*shader_program, *vs);

    glBindAttribLocation(*shader_program, 0, "vertex_position");
    glBindAttribLocation(*shader_program, 1, "vertex_texture");

    glLinkProgram(*shader_program);

    log(LOG_INFO, "Shader created");

    if(!is_valid(*shader_program)){
        log(LOG_INFO, "Shader linked");
    }

    shader_info_log(*fs, 1);
    shader_info_log(*vs, 0);
    shader_program_log(*shader_program);
}
void allocate(GLuint * shader,int * mml, int * vml, int * pml){
    mmlp = mml; vmlp = vml; pmlp = pml;
    *mml = glGetUniformLocation(*shader, "model");
    *vml = glGetUniformLocation(*shader, "view");
    *pml = glGetUniformLocation(*shader, "proj");
    glUseProgram(*shader);
}
void update_matrix(mat4 *pj, mat4 *vw, mat4 *md){
    glUniformMatrix4fv(*pmlp, 1, GL_FALSE, pj->m);
    glUniformMatrix4fv(*vmlp, 1, GL_FALSE, vw->m);
    glUniformMatrix4fv(*mmlp, 1, GL_FALSE, md->m);
}

#endif