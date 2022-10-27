#include "lib/math.hpp"
#include "lib/util.h"
#include "lib/window.h"
#include "lib/reader.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <sstream>
#include <sys/time.h>

int asd = 0;
void update(){
    asd++;
}
int main(){

    log_start();

    const GLchar* p;

    char VS[MAX_FILE_SIZE];
    char FS[MAX_FILE_SIZE];

    int width = 200;
    int height = 200;

    GLint colour_loc;

    if(!AENGCreateWindow(width, height, "CULOCAGAO")){
        std::cout << "EXCEPTION OCURRED\n";
        log(LOG_INFO, "Error while creating frame");
        return -1;
    }
    log(LOG_INFO, "Window created succesfully");

    GLfloat aa[0];

    GLfloat points[]{
        0.0f, 0.5f, 1.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    GLfloat colours[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LESS );

    readfile("./shaders/VS.glsl", VS);
    readfile("./shaders/FS.glsl", FS);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    p = (const GLchar*)VS;
    glShaderSource(vs, 1, &p, NULL);
    glCompileShader(vs);
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    p = (const GLchar*)FS;
    glShaderSource(fs, 1, &p, NULL);
    glCompileShader(fs);

    GLuint shader = glCreateProgram();
    glAttachShader(shader, fs);
    glAttachShader(shader, vs);

    glBindAttribLocation(shader, 0, "vertex_position");
    glBindAttribLocation(shader, 1, "vertex_colour");

    glLinkProgram(shader);

    GLuint PVBO;
    glGenBuffers(1, &PVBO);
    glBindBuffer(GL_ARRAY_BUFFER , PVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);    

    GLuint CVBO;
    glGenBuffers(1, &CVBO);
    glBindBuffer(GL_ARRAY_BUFFER , CVBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colours, GL_STATIC_DRAW);    

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, PVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, CVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    colour_loc = glGetUniformLocation(shader, "inputColour");
    glUseProgram(shader);
    glUniform4f(colour_loc, 1.0f, 0.0f, 0.0f, 1.0f);

    GLfloat matrix[] = {
    1.0f, 0.0f, 0.0f, 0.0f, // first column
    0.0f, 1.0f, 0.0f, 0.0f, // second column
    0.0f, 0.0f, 1.0f, 0.0f, // third column
    0.5f, 0.0f, 0.0f, 1.0f  // fourth column
    };

    int matrix_location = glGetUniformLocation( shader, "matrix" );
    glUseProgram( shader );
    glUniformMatrix4fv( matrix_location, 1, GL_FALSE, matrix );

    glEnable( GL_CULL_FACE ); // cull face
    glCullFace( GL_BACK );    // cull back face
    glFrontFace( GL_CW ); 

    double DI = 1000000000.0/144.0;
    double DELTA = 0.0;

    long int CT;
    long int LT;

    int DC = 0;
    long int TIMER = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);

    while(!AENGClose()) {

        gettimeofday(&tp, NULL);
        CT = tp.tv_sec*1000+tp.tv_usec/1000;
        
        DELTA += (CT-LT)/DI;
        TIMER += (CT-LT);

        LT = CT;

        

        std::cout << "Delta: " << DELTA << std::endl;

        std::cout << "Time" << TIMER << std::endl;


        if(DELTA >= 1){
            AENGUpdate(update, &shader, &VAO);
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