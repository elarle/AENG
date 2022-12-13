#ifndef AENG_TEXTURE
#define AENG_TEXTURE
#define STB_IMAGE_IMPLEMENTATION

#include "texture.hpp"
#include "../utils/stb_image.h"
#include <GL/gl.h>

Texture::Texture(GLuint*p){
    this->p = p;
}
void Texture::setFile(const char* src){
    this->file_name = (char*)src;
}
int Texture::load(){
    if(this->file_name == 0){
        return EMPTY_FILE_PATH;
    }
    unsigned char* img_d = stbi_load(this->file_name, &x,&y,&n, this->fc);
    if(!img_d){
        return 0x01;
    }
    if(p==0){
        return 0x03;
    }
    glGenTextures(n, p);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *p);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_d);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    GLfloat max_a = 0.0f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_a);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_a);
    return 0;
}

#endif