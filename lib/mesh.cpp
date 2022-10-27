#ifndef AENG_MESH
#define AENG_MESH

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
int MESH_SIZE = 0;
std::vector<float> points;
std::vector<int> faces;

void con_faces();
inline void con_faces(){
    std::vector<float> vertices;
    for(int i = 0; i < faces.size(); i++){
        vertices.push_back(points[faces[i]]);
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
        // using printf() in all tests for consistency
        //printf("%s", line);
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
            for(int i = 0; i < 3; i++){points.push_back(pnts[i]);}
            MESH_SIZE+=3;
        }
        if(check[0] == 'f' && check[1] == ' '){
            std::cout << line << "\n";
            std::vector<int> face = parse_faces(line);
            std::cout << "FACES: " << face.size() << "\n";
            
            for(int i = 0; i < 3; i++){faces.push_back(face[i]);}
        }
    }
    con_faces();
    //MESH_SIZE = points.size();
    log(LOG_INFO, "Loaded mesh with size: %i", MESH_SIZE);
    fclose(fp);
    if (line)
        free(line);
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
