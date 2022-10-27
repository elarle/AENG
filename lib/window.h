#ifndef AENG_WINDOW
#define AENG_WINDOW

#include "reader.h"
#include "util.h"
#include <GL/eglew.h>
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
inline void AENGUpdate(void (*update)(), GLuint *shader, GLuint *VAO, int count){

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(*shader);
    glBindVertexArray(*VAO);

    glDrawArrays(GL_TRIANGLES,0, count);

    (*update)();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

//-----SHADER FUNCTIONS-----//
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

#endif