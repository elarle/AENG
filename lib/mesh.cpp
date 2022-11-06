#ifndef AENG_MESH
#define AENG_MESH

#include "console.hpp"
#include "math.hpp"
#include "mesh.hpp"
#include "util.h"
#include <GL/gl.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define VERBOSE 0

int MESH_SIZE = 0;
std::vector<float> points;
std::vector<int> faces;
std::vector<float> colors;

void con_faces();
inline void con_faces(){
    if(VERBOSE)println(WHITE, "Faces: %i, Vertices: %i", faces.size(), points.size());
    for(int a = 0; a < faces.size()/3; a++){
        if(VERBOSE)println(GREEN ,"Face(%i): %i-%i-%i --> %i,%i,%i \n(%f,%f,%f),\n(%f,%f,%f),\n(%f,%f,%f)",
        a, 
        faces[a*3], faces[a*3+1], faces[a*3+2], 
        faces[a*3]-1, faces[a*3+1]-1, faces[a*3+2]-1,
        //      x0                         y0                          z0
        points[(faces[a*3]-1)*3],points[(faces[a*3]-1)*3+1],points[(faces[a*3]-1)*3+2],                    
        //      x1                         y1                          z1
        points[(faces[a*3+1]-1)*3],points[(faces[a*3+1]-1)*3+1], points[(faces[a*3+1]-1)*3+2], 
        //      x2                         y2                          z2
        points[(faces[a*3+2]-1)*3],points[(faces[a*3+2]-1)*3+1],points[(faces[a*3+2]-1)*3+2]
        );
    }
    std::vector<float> vertices;
    for(int i = 0; i < faces.size()/3; i++){
        for(int t = 0; t < 3; t++){
            for(int e = 0; e < 3; e++){
                vertices.push_back(points[(faces[i*3+t]-1)*3+e]);
            }
        }
    }
    points = vertices;
    MESH_SIZE = vertices.size();
}
void loadMesh(const char* file);
inline void loadMesh(const char* file){
    FILE* fp = fopen(file, "r");
    if (fp == NULL){
        log(LOG_WARNING, "Cannot open file %s", file);
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {
        // using if(VERBOSE)printf() in all tests for consistency
        //if(VERBOSE)printf("%s", line);
        /*
        if(strncmp(line, "v", 0) == 0){
            std::vector<float> pnts = parse_float(line);
            for(int i = 0; i < 3; i++){points.push_back(pnts[i]);}
            MESH_SIZE+=3;
        }
        */
        char check[sizeof(line)];
        strncpy(check, line, sizeof(check));
        if(check[0] == 'v' && check[1] == ' '){
            //std::cout << line << "\n";
            std::vector<float> pnts = parse_float(line);
            if(VERBOSE)println(GREEN, "V(%i): %f, %f, %f", pnts.size(), pnts[0], pnts[1], pnts[2]);
            points.push_back(pnts[0]);
            points.push_back(pnts[1]);
            points.push_back(pnts[2]);
            MESH_SIZE+=3;
        }
        if(check[0] == 'f' && check[1] == ' '){
            std::vector<int> face = parse_faces(line);
            faces.push_back(face[0]);
            faces.push_back(face[1]);
            faces.push_back(face[2]);
            // ERROR -> for(int i = 0; i < 3; i++){faces.push_back(face[i]);}
        }
    }
    con_faces();
    //MESH_SIZE = points.size();
    log(LOG_INFO, "Loaded mesh with size: %i", MESH_SIZE);
    fclose(fp);
    if (line)
        free(line);
}
void genMatCap();
inline void genMatCap(){
    for(int i = 0; i < MESH_SIZE/9; i++){
        colors.push_back(1.0f);colors.push_back(0.0f);colors.push_back(0.0f);
        colors.push_back(0.0f);colors.push_back(1.0f);colors.push_back(0.0f);
        colors.push_back(0.0f);colors.push_back(0.0f);colors.push_back(1.0f);
    }
}
void pushColors(float * color_m){
    log(LOG_INFO, "Pushing colors(%i) for faces(%i)", colors.size()/3, MESH_SIZE/3);
    for(int i = 0; i < points.size(); i++){
        *color_m = (GLfloat)points[i];
        color_m++;
    }
}
void pushMesh(float * mesh);
inline void pushMesh(float * mesh){
    log(LOG_INFO, "Pushing points(%i) to mesh(%i)", points.size(), MESH_SIZE);
    for(int i = 0; i < points.size(); i++){
        *mesh = (GLfloat)points[i];
        mesh++;
    }
    log(LOG_INFO, "Push process completed");
}
#endif
