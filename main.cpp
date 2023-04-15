#include "lib/core/camera.h"
#include "lib/core/object.cpp"
#include "lib/core/object.h"
#include "lib/core/shader.cpp"
#include "lib/core/shader.h"
#include "lib/engine/math.h"
#include "lib/engine/window.h"
#include "lib/utils/globals.h"
#include "lib/utils/logger.h"
#include "lib/utils/console.h"
#include "lib/engine/math.cpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <sys/time.h>

shader P_shader;

GLint view_p;
GLint proj_p;
GLint modl_p;

std::vector<object> objs;

vec2 mouse_xy = vec2();
vec2 last_mouse = vec2();

int click_k = 0;
int cursor_visibility = 1;

float scroll_d = 0.0f;

camera cam;

void draw(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    
    glUseProgram(P_shader.program);
 
    for(int i = 0; i < objs.size(); i++){

        //println(BLUE, "%i", 0);
        
        glBindVertexArray(objs[i].VA);
        //objs[i].matrix.print();
        //glEnableVertexAttribArray(objs[i].VA);
        glUniformMatrix4fv(modl_p, 1, GL_FALSE, objs[i].matrix.m);

        glUniform1i(glGetUniformLocation(P_shader.program, "texture_s"), 0);
        
        glUniform3f(glGetUniformLocation(P_shader.program, "camera_pos"), cam.position.x, cam.position.y, cam.position.z);

        objs[i].pre_draw();

        //println(GREEN, "%i", objs[i].malla.SIZE/3); 
        glDrawArrays(GL_TRIANGLES, 0, objs[i].malla.SIZE/3);
        //glDisableVertexAttribArray(objs[i].VA);
        //println(BLUE, "DRAWING %i", objs[i].malla.SIZE);
   
    }
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(){
    log_start();
    log(LOG_INFO, "Starting AENG");

    int width = 480;
    int height = 720;

    if(CreateWindow(&width, &height, "Mi moto alpino derrapante")){}
    addHandlers(&mouse_xy, &click_k, &scroll_d, &cursor_visibility);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, nullptr);

    P_shader = shader();
    P_shader.load(VERTEX_SHADER, FRAGMENT_SHADER);
    glUseProgram(P_shader.program);

    object cube = object();
    cube.load_file("./scene/models/box.obj");

    cube.position = vec3(2, 0, 0);
    
    cube.load();

    cube.texture = material("./scene/textures/tex.png");

/*     object cube2 = object();
    cube2.load_file("./scene/models/cylinder.obj");
    cube2.texture = material("./scene/textures/pene.png");

    cube2.position = vec3(-2, 0, 0);

    cube2.load();
 */
/*     object cube3 = object();
    cube3.load_file("./scene/models/land2.obj");
    cube3.texture = material("./scene/textures/tex2.png");

    cube3.load(); */

    glEnableVertexAttribArray(0);

    int SIZE = 0;

    objs.push_back(cube);
/*     objs.push_back(cube2); */
/*     objs.push_back(cube3); */

/*     objs.push_back(fem);
    objs.push_back(tri);
    objs.push_back(cube);
    objs.push_back(cube);
    objs.push_back(cube); */

    for(int i = 0; i < objs.size(); i++){
        SIZE+=objs[i].malla.SIZE;
        objs[i].update_matrix();
    }

    // ----- CREAR SHADER

    /* glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, objs[1].VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); */
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    

    // ----- CLOCKS

    double FPS = 1000000.0/MAX_FPS;
    double TICK = 1000000.0/TPS_BASE;

    double F_DELTA = 0.0;
    double T_DELTA = 0.0;

    long int CT = 0;
    long int LT = 0;

    float sens = 0.04f;

    int DC = 0;
    int TPS = 0;

    double TIMER = 0.0;

    struct timeval tp;
    gettimeofday(&tp, NULL);

    //-------- CAMERA

    cam = camera();
    
    cam.position.z -= 4;
    cam.position.y = 2;
    cam.rotate(vec3(0, 0, 0));

    cam.speed = 0.01f;

    cam.min = 0.7f;

    cam.max = 1000.0f;

    cam.recalc_view();
    cam.recalc_proj();

    view_p = glGetUniformLocation(P_shader.program, "view");
    proj_p = glGetUniformLocation(P_shader.program, "proj");
    modl_p = glGetUniformLocation(P_shader.program, "model");
    
    GLuint lpos = glGetUniformLocation(P_shader.program, "lpos");

    glUniformMatrix4fv(view_p, 1, GL_FALSE, cam.view.m);
    glUniformMatrix4fv(proj_p, 1, GL_FALSE, cam.proj.m);

    log(LOG_INFO, "Starting main thread");

    cursor_visibility = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    while (!WINDOW_SHOULD_CLOSE()) {

        gettimeofday(&tp, NULL);
        CT = tp.tv_usec;
        F_DELTA += (CT-LT)/FPS;
        T_DELTA += (CT-LT)/TICK;

        //KEYBOARD

        if(pressed(GLFW_KEY_ESCAPE)){
            CloseWindow();
        }

        if(!cursor_visibility){
            /* if(mouse_xy != last_mouse){
                cam.rotate(vec3((mouse_xy.y-last_mouse.y)/sens, (mouse_xy.x-last_mouse.x)/sens, 0.0f));
                last_mouse.x = mouse_xy.x;
                last_mouse.y = mouse_xy.y;
            }  */

            //mouse_xy.print();
            //last_mouse.print();
            //println("------");
            
            if(mouse_xy != last_mouse){
                cam.rotation.y += (mouse_xy.x-last_mouse.x)*sens*RAD;
                cam.rotation.x += (mouse_xy.y-last_mouse.y)*sens*RAD;

                cam.rotation.RAD_FIX();
                /* cam.rotate(vec3((mouse_xy.y-last_mouse.y)/sens, (mouse_xy.x-last_mouse.x)/sens, 0.0f)); */
                last_mouse.x = mouse_xy.x;
                last_mouse.y = mouse_xy.y;

                //println("Sa actualizao -> %f, %f", cam.rotation.x, cam.rotation.y);

                cam.recalc_view();
                cam.recalc_proj();
            }
        }

        //FRAME 

        if(F_DELTA >= 1 || F_DELTA < 0){

            cam.recalc_view();

            glUniformMatrix4fv(view_p, 1, GL_FALSE, cam.view.m);
            glUniformMatrix4fv(proj_p, 1, GL_FALSE, cam.proj.m);  

            draw();

            F_DELTA = 0;
            DC++;
        }

        //TICK

        if(T_DELTA >= 1 || T_DELTA < 0){

            /* for(int i = 0; i < objs.size(); i++){
                //objs[i].move(vec2(0, 1));
                
            } */

            //cam.min += 0.0001f;

            if(pressed(GLFW_KEY_W)){
                cam.move(vec2(0, 1));
            }
            if(pressed(GLFW_KEY_S)){
                cam.move(vec2(1, 1));
            }
            if(pressed(GLFW_KEY_A)){
                cam.move(vec2(0.5, 1));
            }
            if(pressed(GLFW_KEY_D)){
                cam.move(vec2(0.5, -1));
            }

            //cam.position.z+=0.001;

            //objs[0].rotate(vec3(0.0f, 0.01f, 0.0f));
            /* objs[3].rotate(vec3(0.1f, 0.00f, 0.01f));
            objs[4].rotate(vec3(0.1f, 0.00f, -0.2f));
            objs[5].rotate(vec3(0.1f, 0.00f, 0.0f)); */

            cam.rel = (float)width/(float)height;

            //cam.rotate(vec3(0.1, 0.0, 0));
            cam.recalc_view();
            cam.recalc_proj();

            //cam.rotation.print();

            T_DELTA = 0;
            TPS++;
            TIMER+=1.0/128.0;
        }

        //SECONDS

        if(LT > CT){
            std::stringstream ss;
            ss << "Acorn Engine | Alpha 0.2 | FPS: " << DC << " - TPS: " << TPS << " | V: " << SIZE;
            SetTitle(ss.str().c_str());
            TPS = 0;
            DC = 0;
        }

        LT = CT;
        
    }
    println(BLUE, "Program exited %f", TIMER);
    DeleteWindow();
    log(LOG_INFO,"Program ended");
    return 0;
}