#include "lib/globals.h"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/engine/camera.cpp"
#include "lib/utils/console.hpp"
#include "lib/logic/math.cpp"
#include "lib/utils/logger.h"
#include "lib/utils/utils.cpp"
#include "lib/engine/texture.cpp"
#include "lib/engine/mesh.cpp"
#include "lib/core/window.h"
#include "lib/utils/reader.h"
#include "lib/engine/shader.cpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <sys/time.h>
#include <sys/types.h>
#include <vector>

/*
    //---------FORMATTING---------//

    //int -> %d / %i

    //int -> (OCT) -> %o
    //int -> (DEC) -> %u
    //int -> (HEX) -> %x
    
    //float -> %f
    //char -> %c
    //char array -> %s

    //---------POINTERS-----------//

        int direccion = &variable;
        int * puntero = &variable;

        int var = 10;
        int add = &var; (0x00...)
        int * pnt = &var | add;

        load address -> pnt = &var;
        edit value -> *pnt = val;

        *pnt = 20 === var = 20;

    //----------ARRAYS---------//

        int values[5];

        int * pnt;

        pnt = values; => (pnt -> values[0])

        *pnt = 10; => values[0] = 10;

        p++; => (pnt -> values[1])

        *pnt = 20; => values[1] = 20;

        p = &values[1]; => (pnt -> addres-of(values[1]) == pnt -> values[1]);

        "p es un entero, (0), puede ser usado como entero [p = p+1]=[p++]"

        *(p+2) = 30; => p == 0 -> +2 = val[2]; 

*/

int asd = 0;
void update(){
    asd++;
}

//-----MAIN----//

int main(){

    log_start();

    int width = 480;
    int height = 720;

    int left_click = 0;
    int right_clicl = 0;

    vec2 mouse = vec2(0,0);
    vec2 mouse_l = mouse;

    double scroll = 0;

    GLint colour_loc;

    //----------LOAD MODEL----------//

    Mesh malla = Mesh("./models/box.obj", true);

    GLfloat mesh[malla.size], colours[malla.size], maps[malla.size];

    malla.push_mesh(mesh);
    malla.push_colors(colours);
    malla.push_maps(maps);

    glfwSetErrorCallback(err_cb);

    //---------WINDOW INIT----------//    

    if(!AENGCreateWindow(&width, &height, "CULOCAGAO")){
        std::cout << "EXCEPTION OCURRED\n";
        log(LOG_INFO, "Error while creating frame");
        return -1;
    }

    log(LOG_INFO, "Window created succesfully");

    println(GREEN, "Created window W:%i, H: %i", width, height);

    //------TEXTURING------//

    GLuint tex;
    Texture textura_1 = Texture(&tex);
    textura_1.setFile("./textures/01.png");
    int ts = textura_1.load();
    if(ts){
        log(LOG_ERROR, "Error loading texture %he", ts);
    }

    //------CREATE ALL SHADER PARAMETERS------//

    GLuint shader, vs, fs, PVBO, MVBO, VAO;

    point_vbo(&PVBO, MESH_SIZE, mesh);
    maps_vbo(&MVBO, MESH_SIZE, maps);

    create_shaders(&shader, &vs, &fs, &PVBO, &MVBO,&VAO);

    //--------------------CAMARA PARAMETERS INIT---------------------//

    log(LOG_INFO, "Creating camera parameters");

    Camera cam = Camera();

    AENGMousePointers(&mouse, &left_click, &right_clicl, &cam);

    cam.setPosition(0.0f, 10.0f, -10.0f);
    cam.setRotation(0.0f, 0.0f, 0.0f);
    cam.scale(0.1f);
    cam.setProjection(67.0f, (float)width/(float)height, 1.0f, 1000.0f);

    malla.setPosition(vec3(0.0f, 0.0f, 5.0f));

    mat4 model = malla.getMatrix();
    mat4 view = cam.getViewMatrixV2();
    mat4 proj = cam.getProjMatrix();

    proj.m[11] = -1.0f;

    log(LOG_INFO, "Created camera parameters");

    //----------------MATRIX LOCATIONS-------------------//

    GLint mml, vml, pml;
    allocate(&shader,&mml, &vml, &pml);

    glUniformMatrix4fv( vml, 1, GL_FALSE, proj.m );
    glUniformMatrix4fv( pml, 1, GL_FALSE, view.m );

    log(LOG_INFO, "Apliying mesh transforms");

    //------------------SETTINGS---------------------//

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable( GL_CULL_FACE );
    glCullFace( GL_FRONT );
    glFrontFace( GL_CCW ); 

    log(LOG_INFO, "Enabled custom settings");

    //---------------UPDATER VARIABLES---------------//

    double DI = 1000000000.0/144.0;
    double DELTA = 0.0;

    long int CT = 0;
    long int LT = 0;

    float sens = 20.0f;

    int DC = 0;
    long int TIMER = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);

    log(LOG_INFO, "Starting main thread");

    //----------------MAIN LOOP-----------------//

    float fou = 60.0f;

    while(!AENGClose()) {

        //----CLOCK STUFF-----//

        gettimeofday(&tp, NULL);
        CT = tp.tv_sec*1000+tp.tv_usec/1000;
        DELTA += (CT-LT)/DI;
        TIMER += (CT-LT);

        LT = CT;

        //-----TICK-----//

        if(DELTA >= 1){

            cls();
            cam.position.print(RED);
            cam.rotation_r.print(GREEN);
            vec3 dir = vec3(
                sinf(cam.rotation.x)*cosf(cam.rotation.y),
                sinf(cam.rotation.x)*sinf(cam.rotation.y),
                cosf(cam.rotation.x)
            );
            dir.print(BLUE);
            malla.position.print(MAGENTA);
            
            //---MOUSE---//

            if(mouse != mouse_l){
                cam.rotate((mouse.y-mouse_l.y)/sens, (mouse.x-mouse_l.x)/sens, 0.0f);
            }
            mouse_l.x = mouse.x;
            mouse_l.y = mouse.y;

            //---MATRIX UPDATING---//

            model = malla.getMatrix();
            view = cam.getViewMatrixV3();

            cam.projection.y = (float)width/(float)height;

            proj = cam.getProjMatrix();

            update_matrix(&proj, &view, &model);
            AENGUpdate(update, &shader, MESH_SIZE);

            DELTA--;
            DC++;
        }

        //----1 SEC----//

        if(TIMER >= 1000){
            std::stringstream ss;
            ss << "Acorn Engine | alpha 0.1 | FPS: " << DC;
            glfwSetWindowTitle(window, ss.str().c_str());
            TIMER = 0;
            DC = 0;
        }

        //----KEY CHECKING----//

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == 1)
        {
            glfwSetWindowShouldClose(window, true);
        }

        //----MOVEMENT----//

        float sp = 0.1f;
        
        if(glfwGetKey(window, GLFW_KEY_W) == 1){
            cam.moveV2(1, sp);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == 1){
            cam.moveV2(2, sp);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == 1){
            cam.moveV2(3, sp);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == 1){
            cam.moveV2(4, sp);
        }

        //--------MANUAL ROTATION--------//

        if(glfwGetKey(window, GLFW_KEY_RIGHT) == 1){
            cam.setRotation(0, 90, 0);
        }
        if(glfwGetKey(window, GLFW_KEY_LEFT) == 1){
            cam.setRotation(0, -90, 0);
        }
        if(glfwGetKey(window, GLFW_KEY_UP) == 1){
            cam.setRotation(90, 0, 0);
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == 1){
            cam.setRotation(-90, 0, 0);
        }

        //--------FOV--------//
        
        cam.projection.x += scroll/10.0f;

        //------RESTART POS-----//

        if(glfwGetKey(window, GLFW_KEY_R) == 1){
            cam.projection.x = 67.0f;
            malla.position = vec3(0.0f, 0.0f, 0.0f);
            malla.rotation = vec3(0.0f, 0.0f, 0.0f);
            malla.scale = vec3(1.0f, 1.0f, 1.0f);
        }
    }

    //------------END OF PROGRAM--------------//

    std::cout << "PROGRAM COMPLETED, TICKS: " << asd << "\n";
    AENGDeleteWindow();
    log(LOG_INFO, "Program Completed, total ticks: %i", asd);
    return 0;
}
