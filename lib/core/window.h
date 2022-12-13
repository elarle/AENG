#ifndef AENG_WINDOW
#define AENG_WINDOW

#include "../utils/console.hpp"
#include "../logic/math.cpp"
#include "../utils/reader.h"
#include "../utils/logger.h"
#include "../engine/camera.hpp"
#include <GL/eglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

static GLFWwindow* window;
static int * wip;
static int * hep;

static vec2 * mouse;
static double * scr;

static Camera * camera;

static int *right;
static int *left;

static int moved = 0;

//-----WINDOW FUNCTIONS------//

int AENGCreateWindow(int *width, int *height, const char *title);
int AENGDeleteWindow();
int AENGClose();
void getSize(int* width, int* height);
void resized(GLFWwindow *window, int swidth, int sheight);
void key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void key_action();
void AENGUpdate(void *update, GLuint shader, GLuint VAO);
void AENGMousePointers(short int * x, short int * y);

inline void AENGMousePointers(vec2 *v, int*l, int*r, Camera * cam){
    mouse = v;
    left = l;
    right = r;
    camera = cam;
}

inline void key_pressed(GLFWwindow *window, int key, int scancode, int action, int mods){

}
inline void mouse_pressed(GLFWwindow *window, int button, int action, int mods){
    if(button == 1){
        *left = 1;
        return;
    };
    *left = 0;
}
inline void mouse_scroll(GLFWwindow *window, double xoffset, double yoffset){
    camera->projection.x -= yoffset;
}
inline void mouse_moved(GLFWwindow *window, double xpos, double ypos){
    mouse->x += xpos-(*wip/2.0f);
    mouse->y += ypos-(*hep/2.0f);
    glfwSetCursorPos(window, *wip/2.0f, *hep/2.0f);
}

inline void resized(GLFWwindow* window, int width, int height){
    //width = swidth;
    //height = sheight;
    //glfwGetFramebufferSize(window, &width, &height);
    *wip = width;
    *hep = height;
    glViewport(0, 0, width, height);

}
inline int AENGCreateWindow(int *width, int *height, const char *title){
    wip = width;
    hep = height;

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
    window = glfwCreateWindow(*wip, *hep, title, NULL, NULL);
    
    if(!window){
        glfwTerminate();
        log(LOG_ERROR, "Cannot create frame");
        return 0;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSync);
    glfwSetWindowSizeCallback(window, resized);
    glfwSetMouseButtonCallback(window, mouse_pressed);
    glfwSetCursorPosCallback(window, mouse_moved);
    glfwSetScrollCallback(window, mouse_scroll);

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* rnd = glGetString(GL_RENDERER);
    const GLubyte* vrs = glGetString(GL_VERSION);

    if(glfwRawMouseMotionSupported()){
        log(LOG_INFO, "Raw mouse motion supported");
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

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
inline void AENGUpdate(void (*update)(), GLuint *shader, int count){

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(*shader);
    glDrawArrays(GL_TRIANGLES,0, count);

    (*update)();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

//-----SHADER FUNCTIONS-----//


#endif