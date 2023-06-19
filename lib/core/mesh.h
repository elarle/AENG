#ifndef AENG_OBJECT_MESH
#define AENG_OBJECT_MESH

#include "../utils/parser.h"
#include "../utils/console.h"
#include "../utils/logger.h"
#include "../utils/reader.h"

#include <bits/types/FILE.h>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

#include <time.h>

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

    Crono a;
    a.start();

    if(DEBUG)println(MAGENTA, "Allocating space mesh-> %i", sizeof(float) * FACES * 3);
    heap_vertices = new float[FACES*9];
    if(DEBUG)println(MAGENTA, "Allocating space normals-> %i", sizeof(float) * FACES * 3);
    heap_normals = new float[FACES*9];
    if(DEBUG)println(MAGENTA, "Allocating space uvs-> %i", sizeof(float) * FACES * 2);
    heap_uvs = new float[FACES*6];

    int e2 = 0;

   /*  println("%i", FACES*3); */

    for(int i = 0; i < FACES; i++){
        for(int e = 0; e < 3; e++){
            heap_vertices[SIZE+e] = vertices[faces[i]*3+e];
            heap_normals[SIZE+e] = normal[normal_con[i]*3+e];
            /* heap_vertices[SIZE+1] = vertices[(faces[i+1]*3)+1];
            heap_vertices[SIZE+2] = vertices[(faces[i+2]*3)+2]; */

            
        }
        SIZE += 3;

        heap_uvs[UVS] = uv[(uv_con[i])*2]; 
        heap_uvs[UVS+1] = uv[(uv_con[i])*2+1];

        UVS += 2;
    }

    /* for(int i = 0; i < FACES*3; i++){ */
/* 
         println("### I: %i", i*3);
        println("SIZES:      V:%i    |   N:%i    |   U:%i", vertices.size(), normal.size(), uv.size());
        println("PONTERS:    V:%i    |   N:%i    |   U:%i", (faces[i])*3, (normal_con[i])*3, (uv_con[i])*2);
        println("PSIZE:      V:%i    |   N:%i    |   U:%i", faces.size(), normal_con.size(), uv_con.size());
        println("CARA: %i", i/3); */
        

        /* mesh.push_back(vertices[(faces[i])*3]);
        mesh.push_back(vertices[(faces[i])*3+1]);
        mesh.push_back(vertices[(faces[i])*3+2]); 

        heap_vertices[e] = vertices[(faces[i])*3];
        heap_vertices[e+1] = vertices[(faces[i])*3+1];
        heap_vertices[e+2] = vertices[(faces[i])*3+2];

         normals.push_back(normal[(normal_con[i])*3]);
        normals.push_back(normal[(normal_con[i])*3+1]);
        normals.push_back(normal[(normal_con[i])*3+2]); 

        heap_normals[e] = normal[(normal_con[i])*3];
        heap_normals[e+1] = normal[(normal_con[i])*3+1];
        heap_normals[e+2] = normal[(normal_con[i])*3+2];

        e+=3;
        SIZE+=3;

        int a = (uv_con[i]);
        float b = uv[a];
        heap_uvs[e2] = b; 
        heap_uvs[e2+1] = uv[(uv_con[i])*2+1];

        e2+=2;
        UVS+=2; */

    a.end();
}

inline int mesh::load_file(const char *file_name){

    std::vector<int> fc;

    print(GREEN, "Loading: ");println(GREEN, file_name);

    read_bin_f(
        file_name,
        &vertices,
        &normal,
        &uv,
        &fc
    );

    println(GREEN,"Loaded!, processing...");

    /* for(int i = 0; i < vertices.size(); i++){
        println("%f", vertices[i]);
    } */

    for(int i = 0; i < fc.size()-3; i+=3){
        faces.push_back(fc[i]-1);
        uv_con.push_back(fc[i+1]-1);
        normal_con.push_back(fc[i+2]-1);
    }

    VERTICES=vertices.size()*3;
    FACES=faces.size();

    // OLD METHOD (nonbin)

    /* FILE* fp = fopen(file_name, "r");
    if(fp == NULL){return FILE_NOT_FOUND;}
    char* line = NULL;
    size_t len = 0;

    int i = 0;
    int e = 0;

    thide_cursor();

    time_t seconds;
    seconds = time (NULL);
    long int last = seconds;

    if(DEBUG){mv(0, 0);
    println("Loading -> %s", file_name);}

    while((getline(&line, &len, fp)) != -1){

        seconds = time (NULL);

        char check[sizeof(line)];
        strncpy(check, line, sizeof(check));
    
        if(DEBUG){mv(2, 3);
        print(GREEN, " * line -> %i", i);}

        //VERTEX
        if(check[0] == 'v' && check[1] == ' '){
            std::vector<float> pnts = parse_float(line);
            vertices.push_back(pnts[0]);
            vertices.push_back(pnts[1]);
            vertices.push_back(pnts[2]);
            VERTICES+=3;
        }

        //NORMALS
        if(check[0] == 'v' && check[1] == 'n'){
            std::vector<float> pnts = parse_float(line);
            normal.push_back(pnts[0]);
            normal.push_back(pnts[1]);
            normal.push_back(pnts[2]);
        }

        //UVS
        if(check[0] == 'v' && check[1] == 't'){
            std::vector<float> norm = parse_float(line);
            uv.push_back(norm[0]);
            uv.push_back(norm[1]);
        }

        //CONNECTIONS
        if(check[0] == 'f' && check[1] == ' '){
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

        i++;

        if(DEBUG && seconds > last){
            e++;
            mv(2, 4);
            print(RED, " * speed ->  %f lines/s", (float)i/e);
        }

        last = seconds; 
    }*/

    tshow_cursor();

    //mv(0, 8);

    connect_faces();
    /* fclose(fp);
    if(line)free(line);
    return 0; */

    return 0;
}

#endif
