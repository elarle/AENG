#ifndef AENG_MATERIAL_H
#define AENG_MATERIAL_H

#include "../engine/math.cpp"
#include "image.h"
#include <vector>
#include <GL/eglew.h>

struct material{
    material(){}
    material(const char *);

    vec4 color;
    float diffuse = 1;
    float specular = 3;
    float shininess = 50;
    float reflect = 0.5;

    Image img;

    GLuint IMG_ID;
};

inline material::material(const char * file){
    img = Image(file);

    GLuint img_id;
    glGenTextures(1, &img_id);
    glBindTexture(GL_TEXTURE_2D, img_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width, img.height, 0, GL_RGB, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    IMG_ID = img_id;
}

#endif