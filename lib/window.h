#ifndef AENG_WINDOW
#define AENG_WINDOW

#include "console.hpp"
#include "math.cpp"
#include "reader.h"
#include "util.h"
#include <GL/eglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <ostream>

static GLFWwindow* window;

//-----WINDOW FUNCTIONS------//

int AENGCreateWindow(int width, int height, const char *title);
int AENGDeleteWindow();
int AENGClose();
void getSize(int* width, int* height);
void resized(GLFWwindow *window, int swidth, int sheight);
void AENGUpdate(void *update, GLuint shader, GLuint VAO);

inline void resized(GLFWwindow* window, int width, int height){
    //width = swidth;
    //height = sheight;
    //glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    std::cout << width << " - " << height << std::endl;
}
inline int AENGCreateWindow(int width, int height, const char *title){

    log(LOG_INFO, "Creating frame");
    
    if(!glfwInit()){
        log(LOG_ERROR, "Error cannot start glfw");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        //ANTIALIAS
    glfwWindowHint(GLFW_SAMPLES, ANTIALIAS_LEVEL);
    log(LOG_INFO, "Set antialias to: %i", ANTIALIAS_LEVEL);
    //glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if(!window){
        glfwTerminate();
        log(LOG_ERROR, "Cannot create frame");
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, resized);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* rnd = glGetString(GL_RENDERER);
    const GLubyte* vrs = glGetString(GL_VERSION);

    log(LOG_INFO, "System Info: \n  Renderer: %s \n  Version: %s", rnd, vrs);

    return 1;
}
inline int AENGDeleteWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}
inline int AENGClose(){
    return glfwWindowShouldClose(window);
}
inline void AENGUpdate(void (*update)(), GLuint *shader, int count, int m_i, mat4 model_c){

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(*shader);
    for(int i = 0; i < 1; i++){
        glUniformMatrix4fv(m_i, 1, GL_FALSE, model_c.m);
        glDrawArrays(GL_TRIANGLES,0, count);
    }

    (*update)();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

//-----SHADER FUNCTIONS-----//


#endif