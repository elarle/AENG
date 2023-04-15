#ifndef LOG_GL
#define LOG_GL

#include <GL/gl.h>
#include "globals.h"
#include "logger.h"

void log_gl();
inline void log_gl(){
    GLenum error = glGetError();
    switch (error) {
        case GL_NO_ERROR:
            printf("Opengl not error\n");
            //log(LOG_INFO, "Opengl not error");
            break;
        case GL_INVALID_ENUM:
            printf("OpenGL error: GL_INVALID_ENUM\n");
            //log(LOG_INFO, "OpenGL error: GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            printf("OpenGL error: GL_INVALID_VALUE\n");
            //log(LOG_INFO, "OpenGL error: GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            printf("OpenGL error: GL_INVALID_OPERATION\n");
            //log(LOG_INFO, "OpenGL error: GL_INVALID_OPERATION");
            break;
        case GL_STACK_OVERFLOW:
            printf("OpenGL error: GL_STACK_OVERFLOW\n");
            //log(LOG_INFO, "OpenGL error: GL_STACK_OVERFLOW");
            break;
        case GL_STACK_UNDERFLOW:
            printf("OpenGL error: GL_STACK_UNDERFLOW\n");
            //log(LOG_INFO, "OpenGL error: GL_STACK_UNDERFLOW");
            break;
        case GL_OUT_OF_MEMORY:
            printf("OpenGL error: GL_OUT_OF_MEMORY\n");
            //log(LOG_INFO, "OpenGL error: GL_OUT_OF_MEMORY");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            printf("OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION\n");
            //log(LOG_INFO, "OpenGL error: GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
        default:
            printf("Unknown OpenGL error\n");
            //log(LOG_INFO, "Unknown OpenGL error");
            break;
    }
}

#endif