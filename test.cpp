#include <iostream>
#include <ostream>
#include "lib/reader.h"
#include "lib/camera.cpp"
#include "lib/camera.hpp"
#include "lib/mesh.hpp"
#include "lib/util.h"
#include "lib/math.hpp"
#include "lib/math.cpp"
#include "lib/window.h"
#include "lib/reader.h"
#include "lib/mesh.cpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
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

    int width = 200;
    int height = 200;

    GLint colour_loc;

    if(!AENGCreateWindow(width, height, "CULOCAGAO")){
        std::cout << "EXCEPTION OCURRED\n";
        log(LOG_INFO, "Error while creating frame");
        return -1;
    }
    log(LOG_INFO, "Window created succesfully");

    loadMesh("./models/sphere.obj");
    GLfloat mesh[MESH_SIZE];
    pushMesh(mesh);

    log(LOG_INFO, "Mesh created successfully");

    GLfloat points[]{
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f
    };

    /*

    for(GLfloat f : points){
        printf("%f ", f);
    }

printf("\n--------------------------\n");

    for(GLfloat f : mesh){
        printf("%f ", f);
    }

    */

    GLfloat colours[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f,
        
        0.0f, 1.0f,  0.0f,
        1.0f, 0.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LESS );

    log(LOG_INFO, "Enabled custom caps");

    GLuint vs = createVS();
    log(LOG_INFO, "Loading Vertex Shader");
    GLuint fs = createFS();
    log(LOG_INFO, "Loading Fragment Shader");

    GLuint shader = glCreateProgram();
    glAttachShader(shader, fs);
    glAttachShader(shader, vs);

    glBindAttribLocation(shader, 0, "vertex_position");
    glBindAttribLocation(shader, 1, "vertex_colour");

    glLinkProgram(shader);

    log(LOG_INFO, "Shader created");

    GLuint PVBO;
    glGenBuffers(1, &PVBO);
    glBindBuffer(GL_ARRAY_BUFFER , PVBO);
    glBufferData(GL_ARRAY_BUFFER, MESH_SIZE * sizeof(float), mesh, GL_STATIC_DRAW);    

    GLuint CVBO;
    glGenBuffers(1, &CVBO);
    glBindBuffer(GL_ARRAY_BUFFER , CVBO);
    glBufferData(GL_ARRAY_BUFFER, MESH_SIZE * sizeof(float), colours, GL_STATIC_DRAW);    

    log(LOG_INFO, "Generated Vertex Buffers");

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    log(LOG_INFO, "Generated VAO");

    colour_loc = glGetUniformLocation(shader, "inputColour");
    glUseProgram(shader);
    glUniform4f(colour_loc, 1.0f, 0.0f, 0.0f, 1.0f);

    GLfloat matrix[] = {
    1.0f, 0.0f, 0.0f, 0.0f, // first column
    0.0f, 1.0f, 0.0f, 0.0f, // second column
    0.0f, 0.0f, 1.0f, 0.0f, // third column
    0.5f, 0.0f, 0.0f, 1.0f  // fourth column
    };

    float matrix_location = glGetUniformLocation( shader, "matrix" );
    glUseProgram( shader );
    glUniformMatrix4fv( matrix_location, 1, GL_FALSE, matrix );

    //--------------------CAMARA---------------------//

    log(LOG_INFO, "Creating camera parameters");

    Camera cam = Camera();
    cam.setPosition(0.0f, -1.0f, 0.5f);
    cam.setRotation(0.0f, 0.0f, 0.0f);
    cam.setProjection(60.0f, 16.0f/9.0f, 0.1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //------------------SETTINGS---------------------//

    
    glEnable( GL_CULL_FACE );
    //glEnable(GL_DEPTH_TEST); // cull face
    glCullFace( GL_BACK );    // cull back face
    glFrontFace( GL_CW ); 

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

    while(!AENGClose()) {

        gettimeofday(&tp, NULL);
        CT = tp.tv_sec*1000+tp.tv_usec/1000;
        
        DELTA += (CT-LT)/DI;
        TIMER += (CT-LT);

        LT = CT;
/*
        std::cout << "CT: " << CT << std::endl;

        std::cout << "Delta: " << DELTA << std::endl;

        std::cout << "Time" << TIMER << std::endl;
*/
        if(DELTA >= 1){
            AENGUpdate(update, &shader, &VAO, MESH_SIZE);
            DELTA--;
            DC++;
        }
        if(TIMER >= 1000){
            std::stringstream ss;
            ss << "Acorn Engine | alpha 0.1 | FPS: " << DC;
            glfwSetWindowTitle(window, ss.str().c_str());
            TIMER = 0;
            DC = 0;
        }
    }
    std::cout << "PROGRAM COMPLETED, TICKS: " << asd << "\n";
    AENGDeleteWindow();
    log(LOG_INFO, "Program Completed, total ticks: %i", asd);
    return 0;
}
