#ifndef AENG_READER
#define AENG_READER

#include "logger.h"
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <sys/stat.h>
#include <vector>

#define VERTICESP    6755399441053.000000
#define NORMALSP     6755399441054.000000
#define UVSP         6755399441055.000000
#define INDICESP     6755399441056.000000
#define ENDP         -1

int size(const char *name);
int readfile(const char *name);

inline int size(const char *name){
    struct stat stat_buf;
    int rc = stat(name, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
inline int filesize(const char* name){
    int length = 0;
    std::ifstream file(name, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    // Seek to the end of the file
    file.seekg(0, std::ios::end);

    // Get the file length
    length = file.tellg();

    // Move back to the beginning of the file
    file.seekg(0, std::ios::beg);

    file.close();

    return length;
}
inline int readfile(const char* name, char* data_string){
    FILE* file = fopen(name, "r");

    if(!file){return 0;}

    size_t cnt = fread( data_string, 1, MAX_FILE_SIZE-1, file);

    if((int)cnt > MAX_FILE_SIZE){return 0;}
    if(std::ferror(file)){
        fclose(file);
        log(LOG_WARNING, "Error opening file: %s", name);
        return 0;
    }

    data_string[cnt] = 0;

    fclose(file);

    return 1;
}

inline int readfile(const char* name, char* data_string, int size){
    FILE* file = fopen(name, "r");

    if(!file){return 0;}

    size_t cnt = fread( data_string, 1, size-1, file);

    if((int)cnt > size){return 0;}
    if(std::ferror(file)){
        fclose(file);
        log(LOG_WARNING, "Error opening file: %s", name);
        return 0;
    }

    data_string[cnt] = 0;

    fclose(file);

    return 1;
}

//      BIN VERTEX FILE READER

inline void read_bin_f(
    const char * file,
    std::vector<float>*vertices,
    std::vector<float>*normals,
    std::vector<float>*uvs,
    std::vector<int>*faces
){

    Crono a;
    a.start();

    int fs = filesize(file);
    char * data = new char[fs];

    readfile(file, data, fs);

    unsigned char * reader8 = new unsigned char[8];

    unsigned char * reader4_1 = new unsigned char[4];
    unsigned char * reader4_2 = new unsigned char[4];

    double * vald = new double;
    float * valf = new float;
    int * vali1 = new int;
    int * vali2 = new int;

    *vald = 0.0;
    *valf = 0.0f;
    *vali1 = 0;
    *vali2 = 0;

    int fase = 0;
    int asd = 0;

    /*
    0 -> Vertices
    1 -> Normales
    2 -> UVS
    3 -> Indices
    */

    for(int i = 0; i < fs/4; i++){

        asd = i;

        //println("SIZE: %x, DIR: %x, D->%s", fs, i*8, (data[(8*(int)i)]));

        for(int e = 0; e < 4; e++){
            //print(RED, "%x ", (int)(data[(8*(int)i)+e]));
            reader4_1[e] = (data[(4*(int)i)+e]);
        }

        switch (fase) {
            case 0:{
                //LOADS THE VERTICES
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)VERTICESP){
                    /* println("Vertices start"); */
                    fase++;
                    break;
                }
            }
            case 1:{
                //LOADS THE NORMALS
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)NORMALSP){
                    /* println("Normals start"); */
                    fase++;
                    break;
                }
                vertices->push_back(*valf);
                break;
            }
            case 2:{
                //LOADS THE UVS
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)UVSP){
                    /* println("UVS start"); */
                    fase++;
                    break;
                }
                normals->push_back(*valf);
                break;
            }
            case 3:{
                //LOADS THE INDICES
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)INDICESP){
                    /* println("Indices start"); */
                    fase++;
                    break;
                }
                uvs->push_back(*valf);
                break;
            }
            case 4:{

                if(*vali1 == ENDP){
                }
                vali1 = reinterpret_cast<int*>(reader4_1);
                if(*vali1 != 0 && *vali1 != -1)faces->push_back(*vali1);
                
                //if(*vali1 == END && *vali2 == END){

                    /* for(double a : vertices)print(GREEN, "V:%f | ", a);
                    println("");
                    for(double a : normal)print(GREEN, "N:%f | ", a);
                    println("");
                    for(double a : uv)print(GREEN, "UV:%f | ", a);
                    println("");
                    for(int a : face)print(GREEN, "FACE:%i | ", a); 

                    fase++;
                    break;
                }
                //println("%f", *vald);
                
                for(int e = 0; e < 4; e++){
                    reader4_1[e] = reader8[e];
                    reader4_2[e] = reader8[e+4];
                }
               
                vali1 = reinterpret_cast<int*>(reader4_1);
                vali2 = reinterpret_cast<int*>(reader4_2);

                if(*vali1 != 0 && *vali1 != -1)face.push_back(*vali1);
                if(*vali2 != 0 && *vali2 != -1)face.push_back(*vali2);

                //println("%i", *vali1);

                break;
                */
            }
        }
        

        /* if(*valf == (float)VERTICES){
            println("VERT -> %f", *vald);
        }
        if(*valf == (float)NORMALS){
            println("NORM -> %f", *vald);
        }
        if(*valf == (float)UVS){
            println("UVS -> %f", *vald);
        }
        if(*valf == (float)INDICES){
            println("INDX -> %f", *vald);
        }
        if(*valf == (float)END){
            println("END -> %f", *vald);
        }  */
        //println("(0x%X-0x%X) %f", 4*i, 4*i+3, *valf);
    }
    a.end();
}


#endif