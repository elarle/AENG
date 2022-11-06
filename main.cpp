#include "lib/camera.cpp"
#include "lib/console.hpp"
#include "lib/math.hpp"
#include "lib/mesh.hpp"
#include "lib/util.h"
#include "lib/math.cpp"
#include "lib/window.h"
#include "lib/reader.h"
#include "lib/mesh.cpp"
#include "lib/shader.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <sys/time.h>

    //---------FORMATTING---------//

    //int -> %d / %i

    //int -> (OCT) -> %o
    //int -> (DEC) -> %u
    //int -> (HEX) -> %x
    
    //float -> %f
    //char -> %c
    //char array -> %s

    //---------POINTERS-----------//

    /***
        int direccion = &variable;
        int * puntero = &variable;

        int var = 10;
        int add = &var; (0x00...)
        int * pnt = &var | add;

        load address -> pnt = &var;
        edit value -> *pnt = val;

        *pnt = 20 === var = 20;
    ***/

    //----------ARRAYS---------//

    /***
        int values[5];

        int * pnt;

        pnt = values; => (pnt -> values[0])

        *pnt = 10; => values[0] = 10;

        p++; => (pnt -> values[1])

        *pnt = 20; => values[1] = 20;

        p = &values[1]; => (pnt -> addres-of(values[1]) == pnt -> values[1]);

        "p es un entero, (0), puede ser usado como entero [p = p+1]=[p++]"

        *(p+2) = 30; => p == 0 -> +2 = val[2]; 


    ***/

int asd = 0;
void update(){
    asd++;
}
int main(){

    log_start();

    int width = 480;
    int height = 720;

    GLint colour_loc;

    //----------MODEL LOADING----------//

    loadMesh("./models/sphere.obj");
    GLfloat mesh[MESH_SIZE];
    GLfloat colours[MESH_SIZE];
    pushMesh(mesh);
    genMatCap();
    pushColors(colours);
    

    log(LOG_INFO, "Model loaded, (%i) -> %i bytes", MESH_SIZE/3, MESH_SIZE * sizeof(float));
    glfwSetErrorCallback(err_cb);

    //---------WINDOW INIT----------//    

    if(!AENGCreateWindow(width, height, "CULOCAGAO")){
        std::cout << "EXCEPTION OCURRED\n";
        log(LOG_INFO, "Error while creating frame");
        return -1;
    }
    log(LOG_INFO, "Window created succesfully");

    println(GREEN, "Created window W:%i, H: %i", width, height);

    //------SHADER CREATION------//

    GLuint vs = createVS();
    log(LOG_INFO, "Loaded Vertex Shader");
    GLuint fs = createFS();
    log(LOG_INFO, "Loaded Fragment Shader");

    GLuint PVBO, CVBO;
    point_vbo(&PVBO, MESH_SIZE, mesh);
    color_vbo(&CVBO, MESH_SIZE, colours);

    log(LOG_INFO, "Generated Vertex Buffers");

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    log(LOG_INFO, "Generated VAO");

    //------SHADER LINKING------//

    GLuint shader = glCreateProgram();
    glAttachShader(shader, fs);
    glAttachShader(shader, vs);

    glBindAttribLocation(shader, 0, "vertex_position");
    glBindAttribLocation(shader, 1, "vertex_color");

    glLinkProgram(shader);

    shader_info_log(fs, 1);
    shader_info_log(vs, 0);
    shader_program_log(shader);

    if(!is_valid(shader)){
        log(LOG_INFO, "Shader linked");
    }

    //--------------------CAMARA---------------------//

    log(LOG_INFO, "Creating camera parameters");

    Camera cam = Camera();

    cam.setPosition(10.0f, 0.0f, 0.5f);
    cam.setRotation(0.0f, 180.0f, 0.0f);
    cam.scale(0.8f);
    cam.setProjection(150.0f*RAD, 16.0f/9.0f, 0.1f, 100.0f);

    mat4 proj = cam.getDefaultProj();
    mat4 view = cam.getViewMatrix();

    GLint model_mat_location = glGetUniformLocation( shader, "model" );
    GLint view_mat_location = glGetUniformLocation( shader, "view" );
    GLint proj_mat_location = glGetUniformLocation( shader, "proj" );

    glUseProgram(shader);
    glUniformMatrix4fv( view_mat_location, 1, GL_FALSE, view.m );
    glUniformMatrix4fv( proj_mat_location, 1, GL_FALSE, proj.m );

    mat4 model_mat[1];
    model_mat[0] = translate( identity_mat4(), vec3(0.0f, 0.0f, 0.0f));

    println(YELLOW, "CAM ROT = %f", cam.rotation.x);

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

    int DC = 0;
    long int TIMER = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);

    log(LOG_INFO, "Starting main thread");

    //----------------MAIN LOOP-----------------//

    while(!AENGClose()) {

        //----CLOCK STUFF-----//

        gettimeofday(&tp, NULL);
        CT = tp.tv_sec*1000+tp.tv_usec/1000;
        DELTA += (CT-LT)/DI;
        TIMER += (CT-LT);
        LT = CT;

        //-----TICK-----//

        if(DELTA >= 1){
            cam.rotate(0.5f, 0.5f, 0.5f);
            glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, cam.getViewMatrix().m);
            AENGUpdate(update, &shader, MESH_SIZE, model_mat_location, model_mat[0]);
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
    }

    //------------END OF PROGRAM--------------//

    std::cout << "PROGRAM COMPLETED, TICKS: " << asd << "\n";
    AENGDeleteWindow();
    log(LOG_INFO, "Program Completed, total ticks: %i", asd);
    return 0;
}
