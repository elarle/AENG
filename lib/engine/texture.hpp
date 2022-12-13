#ifndef AENG_TEXTURE_H
#define AENG_TEXTURE_H

#define EMPTY_FILE_PATH 0x02

#include <GL/gl.h>

struct Texture;
struct Texture{
    Texture();
    Texture(GLuint*p);
    char* file_name;
    int x, y, n;
    int fc = 4;
    GLuint* p;
    void setFile(const char*src);
    int load();
};

#endif