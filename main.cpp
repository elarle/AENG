#include "lib/core/camera.h"
#include "lib/core/light.h"
#include "lib/core/object.cpp"
#include "lib/core/object.h"
#include "lib/core/shader.cpp"
#include "lib/core/shader.h"
#include "lib/engine/math.h"
#include "lib/engine/window.h"
#include "lib/scene/scene.h"
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

// LOCATIONS 

GLuint texture_s;
GLuint cam_pos;

GLuint light_pos;
GLuint light_col;

std::vector<object> objs;
std::vector<light> lights;

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

    for(int e = 0; e < lights.size(); e++){

        glUniform3f(light_pos, lights[e].pos.x, lights[e].pos.y, lights[e].pos.z);
        glUniform3f(light_col, lights[e].color.x, lights[e].color.y, lights[e].color.z);
        glUniform3f(cam_pos, cam.position.x, cam.position.y, cam.position.z);

        for(int i = 0; i < objs.size(); i++){

            
            glBindVertexArray(objs[i].VA);
            //objs[i].matrix.print();
            //glEnableVertexAttribArray(objs[i].VA);
            glUniformMatrix4fv(modl_p, 1, GL_FALSE, objs[i].matrix.m);

            glUniform1i(texture_s, 0);


            objs[i].pre_draw();

            //println(GREEN, "%i", objs[i].malla.SIZE/3); 
            glDrawArrays(GL_TRIANGLES, 0, objs[i].malla.SIZE/3);
            //glDisableVertexAttribArray(objs[i].VA);
            //println(BLUE, "DRAWING %i", objs[i].malla.SIZE);

            

        }

        
        
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

    if(OGL_DEBUG){
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debugCallback, nullptr);
    }

    P_shader = shader();
    P_shader.load(VERTEX_SHADER, FRAGMENT_SHADER);
    glUseProgram(P_shader.program);

    texture_s = glGetUniformLocation(P_shader.program, "texture_s");
    cam_pos = glGetUniformLocation(P_shader.program, "camera_pos");
    light_pos = glGetUniformLocation(P_shader.program, "light_pos");
    light_col = glGetUniformLocation(P_shader.program, "light_color");

    Scene scena = Scene("./scene/scene.dat");
    scena.load();

    object cube = object();
    cube.load_file("./scene/compiled/lady.dat");
    cube.scale = vec3(10, 10, 10);
    cube.update_matrix();
    cube.load();
    cube.texture = material("./scene/textures/uvgrid.png");

    object cube2 = object();
    cube2.load_file("./scene/compiled/sphere.dat");
    cube2.scale = vec3(10, 10, 10);
    cube2.update_matrix();
    cube2.load();
    cube2.texture = material("./scene/textures/uvgrid.png");

    object floor = object();
    floor.load_file("./scene/compiled/floor.dat");
    floor.load();
    floor.texture = material("./scene/textures/uvgrid.png");

    glEnableVertexAttribArray(0);

    int SIZE = 0;

    objs.push_back(cube);
    objs.push_back(cube2);
    objs.push_back(floor);

    light light1 = light();
    light1.color = vec4(1.0, 1.0, 0.0, 1.0);
    light1.pos = vec3(0.0, 2.0, 0.0);
    light light2 = light();
    light2.color = vec4(1.0, 1.0, 0.0, 1.0);
    light2.pos = vec3(1.0, -2.0, 0.0);
    lights.push_back(light1);
    lights.push_back(light2);

    for(int i = 0; i < objs.size(); i++){
        SIZE+=objs[i].malla.SIZE;
        objs[i].update_matrix();
    }

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

    glUniformMatrix4fv(view_p, 1, GL_FALSE, cam.view.m);
    glUniformMatrix4fv(proj_p, 1, GL_FALSE, cam.proj.m);

    log(LOG_INFO, "Starting main thread");

    cursor_visibility = 0;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glShadeModel(GL_FLAT);

    // SHADOWS!!

    unsigned int depth_map_FBO;
    glGenBuffers(1, &depth_map_FBO);

    /* const unsigned int shadow_width = 1024, shadow_height = 1024;

    unsigned int depth_map;
    glGenTextures(1, &depth_map);
    
    glBindTexture(GL_TEXTURE_2D, depth_map);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_FBO);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, shadow_height, shadow_width);

    //PASS LIGHT MATRIX
    glUniform3f(cam_pos, lights[0].pos.x, lights[0].pos.y, lights[0].pos.z);

    glClear(GL_DEPTH_BUFFER_BIT);
    draw();
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_FBO); */

    while (!WINDOW_SHOULD_CLOSE()) {

        gettimeofday(&tp, NULL);
        CT = tp.tv_usec;
        F_DELTA += (CT-LT)/FPS;
        T_DELTA += (CT-LT)/TICK;

        //KEYBOARD

        if(pressed(GLFW_KEY_ESCAPE)){
            CloseWindow();
        }

        //lights[0].pos.x = sinf(TIMER)*4;
        //lights[0].color.x = sinf(TIMER/10);
        //lights[1].pos.y = sinf(TIMER)*4;

        if(!cursor_visibility){
            
            if(mouse_xy != last_mouse){
                cam.rotation.y += (mouse_xy.x-last_mouse.x)*sens*RAD;
                cam.rotation.x += (mouse_xy.y-last_mouse.y)*sens*RAD;

                cam.rotation.RAD_FIX();
                last_mouse.x = mouse_xy.x;
                last_mouse.y = mouse_xy.y;

                cam.recalc_view();
                cam.recalc_proj();
            }
        }



        //FRAME 

        if(F_DELTA >= 1 || F_DELTA < 0){

            //lights[0].color.print();
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
            if(pressed(GLFW_KEY_U)){
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            }
            if(pressed(GLFW_KEY_I)){
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            }
            if(pressed(GLFW_KEY_O)){
                glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
            }
            if(pressed(GLFW_KEY_R)){
                P_shader.load(VERTEX_SHADER, FRAGMENT_SHADER);
            }
            if(pressed(GLFW_KEY_L)){
                cursor_visibility = !(bool)cursor_visibility;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN - cursor_visibility);
            }

            

            //cam.position.z+=0.001;

            lights[0].color = vec4(cosf(TIMER/2)+1, sinf(TIMER/2)+1, 0.0f, 0.0f);

            objs[1].position = vec3(sinf(TIMER/3)*2, 1.5, cosf(TIMER/3)*4);

            //objs[1].rotation = vec3(cosf(TIMER/2)+1, sinf(TIMER/2)+1, 0.0f);
            objs[1].update_matrix();
/*             objs[1].rotate(vec3(0.0f, -sinf(TIMER)/10, 0.0f));
            objs[0].rotate(vec3(0.0f, sinf(TIMER)/10, 0.0f)); */
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