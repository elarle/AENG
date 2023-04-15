#ifndef AENG_SHADER_H
#define AENG_SHADER_H

#include <GL/gl.h>

struct shader{

    shader();

    GLuint program;

    GLuint vertex;
    GLuint fragment;

    const char * VS_FILE;
    const char * FS_FILE;

    int load(const char * vs, const char * fs);
    int reload();
};

#endif