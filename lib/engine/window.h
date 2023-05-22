#ifndef AENG_WINDOW_H
#define AENG_WINDOW_H

#include <GL/eglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../utils/logger.h"
#include "../utils/lgl.h"
#include "./math.cpp"

void resized(GLFWwindow * window, int width, int height);

static GLFWwindow* window;

static int * show_cursor;

static int * wp;
static int * hp;

static int * click;
static float * scroll;

static vec2 * mouse;

static int WINDOW_SHOULD_CLOSE();

int CreateWindow(int*width ,int*height ,const char * title);

void CloseWindow();
void DeleteWindow();

void SetTitle(const char * TITLE);

void resize(GLFWwindow * window, int width, int height);
int pressed(int code);

inline void resize(GLFWwindow * window, int width, int height){
    *wp = width;
    *hp = height;
    glViewport(0, 0, width, height);
};

inline void err_cb(int err, const char* err_msg){
    log(LOG_ERROR, "GLFW ERROR: %s", err_msg);
}

inline void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    // Print the debugging message to the console
    printf("OpenGL Debug Message: %s\n", message);
}


inline void mouse_pressed(GLFWwindow * window, int button, int action, int mods){
    *click = button;
}

inline void mouse_moved(GLFWwindow * window, double xpos, double ypos){
    //mouse->print();
    //println(BLUE, "%i" ,*show_cursor);
    if(!(*show_cursor)){
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        mouse->x += xpos-(*wp/2.0f);
        mouse->y += ypos-(*hp/2.0f);
        glfwSetCursorPos(window, *wp/2.0f, *hp/2.0f);
        return;
    }
    mouse->x = xpos;
    mouse->y = ypos;
}

inline void mouse_scroll(GLFWwindow * window, double xoff, double yoff){
    *scroll = yoff;
}

inline void addHandlers(vec2 * mouse_p, int * click_p, float * scroll_p, int * show_cursor_p){
    show_cursor = show_cursor_p;
    mouse = mouse_p;
    click = click_p;
    scroll = scroll_p;
}

inline int CreateWindow(int * width, int * height, const char * title){

    wp = width; hp = height;
    log(LOG_INFO, "GL init");

    if(!glfwInit()){
        log(LOG_ERROR, "Cannot start glfw");
        return 1;
    }

    glfwSetErrorCallback(err_cb);    

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindowHint(GLFW_SAMPLES, ANTIALIAS_LEVEL);
    log(LOG_INFO, "Antialias set to: %i", ANTIALIAS_LEVEL);

    window = glfwCreateWindow(*wp, *hp, title, NULL, NULL);

    if(!window){
        glfwTerminate();
        log(LOG_ERROR, "Cannot start window");
        return 2;
    }

    glfwSetWindowSizeCallback(window, resize);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSync);

    //glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte* rnd = glGetString(GL_RENDERER);
    const GLubyte* vrs = glGetString(GL_VERSION);

    log(LOG_INFO, "System Info: \n  Renderer: %s \n  Version: %s", rnd, vrs);

    if(glfwRawMouseMotionSupported()){
        log(LOG_INFO, "Raw mouse motion supported");
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glfwSetWindowSizeCallback(window, resize);
    glfwSetMouseButtonCallback(window, mouse_pressed);
    glfwSetCursorPosCallback(window, mouse_moved);
    glfwSetScrollCallback(window, mouse_scroll);

    return 0;
};


inline void CloseWindow(){
    glfwSetWindowShouldClose(window, 1);
}
inline void DeleteWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}


inline void SetTitle(const char *TITLE){
    glfwSetWindowTitle(window, TITLE);
}

inline int pressed(int code){
    if(glfwGetKey(window, code))return 1;
    return 0;
}
int WINDOW_SHOULD_CLOSE(){
    return glfwWindowShouldClose(window);
}

#endif