#ifndef AENG_OBJECT_MESH
#define AENG_OBJECT_MESH

#include "../utils/parser.h"
#include "../utils/console.h"
#include "../utils/logger.h"

#include <bits/types/FILE.h>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

#define FILE_NOT_FOUND 1;

struct mesh{

    long int SIZE = 0;

    long int FACES = 0;

    long int VERTICES = 0;
    long int UVS = 0;

    std::vector<float> mesh;
    std::vector<float> vertices;

    std::vector<float> uvs;
    std::vector<float> uv;

    std::vector<float> normals;
    std::vector<float> normal;

    std::vector<int> faces;
    std::vector<int> uv_con;
    std::vector<int> normal_con;

    float * heap_vertices = new float();
    float * heap_normals = new float();
    float * heap_uvs = new float();

    #define MESH_DEBUG 0

    int load_file(const char * file_name);

    private:
    void connect_faces();

};

inline void mesh::connect_faces (){
    /* for(int i = 0; i < FACES; i++){
        //println(RED, "%i", i);
        for(int t = 0; t < 3; t++){
            for(int e = 0; e < 3; e++){
                //print(RED, "%i ,", faces[i*3+t]);
                println(YELLOW, "%i -> [%i,%i] == V(%i)/V(%i)", faces[i], t, e, (faces[i]-1)*3+(t*3)+e, (faces[i*3+t]-1)*3+e);
                mesh.push_back(vertices[(faces[i*3+t]-1)*3+e]);
                SIZE++;
            }
        }
    } */

    println("Allocating space mesh-> %i", sizeof(float) * FACES * 3);
    heap_vertices = new float[FACES*9];
    println("Allocating space normals-> %i", sizeof(float) * FACES * 3);
    heap_normals = new float[FACES*9];
    println("Allocating space uvs-> %i", sizeof(float) * FACES * 2);
    heap_uvs = new float[FACES*6];

    int e = 0;
    int e2 = 0;

    println("%i", FACES*3);

    for(int i = 0; i < FACES*3; i++){
        /* mesh.push_back(vertices[(faces[i])*3]);
        mesh.push_back(vertices[(faces[i])*3+1]);
        mesh.push_back(vertices[(faces[i])*3+2]); */

        heap_vertices[e] = vertices[(faces[i])*3];
        heap_vertices[e+1] = vertices[(faces[i])*3+1];
        heap_vertices[e+2] = vertices[(faces[i])*3+2];
        
        /* normals.push_back(normal[(normal_con[i])*3]);
        normals.push_back(normal[(normal_con[i])*3+1]);
        normals.push_back(normal[(normal_con[i])*3+2]); */

        heap_normals[e] = normal[(normal_con[i])*3];
        heap_normals[e+1] = normal[(normal_con[i])*3+1];
        heap_normals[e+2] = normal[(normal_con[i])*3+2];

        e+=3;
        SIZE+=3;

        heap_uvs[e2] = uv[(uv_con[i])*2];
        heap_uvs[e2+1] = uv[(uv_con[i])*2+1];

        e2+=2;
        UVS+=2;
    }
}

inline int mesh::load_file(const char *file_name){
    FILE* fp = fopen(file_name, "r");
    if(fp == NULL){return FILE_NOT_FOUND;}
    char* line = NULL;
    size_t len = 0;
    while((getline(&line, &len, fp)) != -1){
        char check[sizeof(line)];
        strncpy(check, line, sizeof(check));

            //VERTEX
        if(check[0] == 'v' && check[1] == ' '){
            std::vector<float> pnts = parse_float(line);
            vertices.push_back(pnts[0]);
            vertices.push_back(pnts[1]);
            vertices.push_back(pnts[2]);
            VERTICES+=3;
        }

        if(check[0] == 'v' && check[1] == 'n'){
            std::vector<float> pnts = parse_float(line);
            normal.push_back(pnts[0]);
            normal.push_back(pnts[1]);
            normal.push_back(pnts[2]);
            VERTICES+=3;
        }

            //MAPS
        if(check[0] == 'v' && check[1] == 't'){
            std::vector<float> norm = parse_float(line);
            uv.push_back(norm[0]);
            uv.push_back(norm[1]);
            //UVS+=2;
        }

        //CONNECTIONS
        if(check[0] == 'f' && check[1] == ' '){
            print(NORMAL, "");
            std::vector<int> data = parse_faces(line);
            faces.push_back(data[1]-1);
            uv_con.push_back(data[2]-1);
            normal_con.push_back(data[3]-1);
            faces.push_back(data[4]-1);
            uv_con.push_back(data[5]-1);
            normal_con.push_back(data[6]-1);
            faces.push_back(data[7]-1);
            uv_con.push_back(data[8]-1);
            normal_con.push_back(data[9]-1);
            FACES++;
        }
    }

    connect_faces();

    fclose(fp);
    if(line)free(line);
    return 0;
};

#endif
