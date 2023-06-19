#include "lib/utils/logger.h"
#include "lib/utils/parser.h"
#include "lib/utils/reader.h"
#include "lib/utils/console.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <vector>

#define DIR "./scene/compiled/lady.dat"
#define TTF "./scene/models/lady.obj"

std::ofstream outputFile;

#define INT = 0x01

// 0x01, byte1 ... byte4

#define FLOAT = 0x02

// 0x02, byte1 ... byte4

#define STRING = 0x05

// 0x05, byte1 ... byten, 0x00

#define VERTICESF   0xffad33
#define NORMALSF    0xffad34
#define UVSF        0xffad35

#define INDICESF    0xffad36

#define ENDF        0xffad37

#define VERTICES    6755399441053.000000
#define NORMALS     6755399441054.000000
#define UVS         6755399441055.000000

#define INDICES     6755399441056.000000

#define END         -1


void write_buffer(std::ofstream * file, char * buffer){
    file->write(buffer, sizeof(buffer));
}
void write_buffer(std::ofstream * file, const char * buffer){
    file->write(buffer, strlen(buffer));
}
void write_buffer(std::ofstream * file, int * buffer, int buffer_size){
    char buff[buffer_size];
    for(int i = 0; i < buffer_size; i++){
        buff[i] = buffer[i];
    }
    file->write(buff, sizeof(buff));
}

void write_double(double a){
    outputFile.write( reinterpret_cast<const char*>( &a ), sizeof( double ));
}
void write_float(float a){
    outputFile.write( reinterpret_cast<const char*>( &a ), sizeof( float ));
}
void write_int(int a){
    outputFile.write( reinterpret_cast<const char*>( &a ), sizeof( int ));
}

// DOUBLE SAVES (8bits)

void read_bin(const char * file){

    std::vector<double> vertices;
    std::vector<double> normal;
    std::vector<double> uv;

    std::vector<int> face;
    std::vector<double> mesh;

    std::vector<int> norm;
    std::vector<double> normals;

    std::vector<int> uvs;
    std::vector<double> uv_map;

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

    for(int i = 0; i < fs/8; i++){

        asd = i;

        //println("SIZE: %x, DIR: %x, D->%s", fs, i*8, (data[(8*(int)i)]));

        for(int e = 0; e < 8; e++){
            //print(RED, "%x ", (int)(data[(8*(int)i)+e]));
            reader8[e] = (data[(8*(int)i)+e]);
        }

        switch (fase) {
            case 0:{
                //LOADS THE VERTICES
                vald = reinterpret_cast<double*>(reader8);
                if(*vald == (double)VERTICES){
                    /* println("Vertices start"); */
                    fase++;
                }
                break;
            }
            case 1:{
                //LOADS THE NORMALS
                vald = reinterpret_cast<double*>(reader8);
                if(*vald == (double)NORMALS){
                    /* println("Normals start"); */
                    fase++;
                    break;
                }
                vertices.push_back(*vald);
                break;
            }
            case 2:{
                //LOADS THE UVS
                vald = reinterpret_cast<double*>(reader8);
                if(*vald == (double)UVS){
                    /* println("UVS start"); */
                    fase++;
                    break;
                }
                normal.push_back(*vald);
                break;
            }
            case 3:{
                //LOADS THE INDICES
                vald = reinterpret_cast<double*>(reader8);
                if(*vald == (double)INDICES){
                    /* println("Indices start"); */
                    fase++;
                    break;
                }
                uv.push_back(*vald);
                break;
            }
            case 4:{
                
                if(*vali1 == END && *vali2 == END){

                    /* for(double a : vertices)print(GREEN, "V:%f | ", a);
                    println("");
                    for(double a : normal)print(GREEN, "N:%f | ", a);
                    println("");
                    for(double a : uv)print(GREEN, "UV:%f | ", a);
                    println("");
                    for(int a : face)print(GREEN, "FACE:%i | ", a); */

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
            }
        }
        

        /* if(*vald == (double)VERTICES){
            println("VERT -> %f", *vald);
        }
        if(*vald == (double)NORMALS){
            println("NORM -> %f", *vald);
        }
        if(*vald == (double)UVS){
            println("UVS -> %f", *vald);
        }
        if(*vald == (double)INDICES){
            println("INDX -> %f", *vald);
        }
        if(*vald == (double)END){
            println("END -> %f", *vald);
        } */
        //println("(0x%X-0x%X) %f", 8*i, 8*i+7, *vald);
    }
    a.end();
}
void make_bin(const char * filein, const char * fileout){

    Crono a;
    

    std::vector<float> vertices;
    std::vector<float> normal;
    std::vector<float> uv;

    outputFile = std::ofstream(fileout, std::ios::binary);
    FILE* fp = fopen(filein, "r");
    if(fp == NULL){return;}
    char* line = NULL;
    size_t len = 0;

    int fase = 0;

    a.start();

    while((getline(&line, &len, fp)) != -1){
        if(line[0] == 'v' && line[1] == ' '){
            if(fase == 0){
                write_double((double)VERTICES);
                fase++;
            }
            //vertice
            std::vector<float> pnts = parse_float(line);
            write_double((double)pnts[0]);
            write_double((double)pnts[1]);
            write_double((double)pnts[2]);
        }
        if(line[0] == 'v' && line[1] == 'n'){
            if(fase == 1){
                write_double((double)NORMALS);
                fase++;
            }
            std::vector<float> pnts = parse_float(line);
            write_double((double)pnts[0]);
            write_double((double)pnts[1]);
            write_double((double)pnts[2]);
            //normal
        }
        if(line[0] == 'v' && line[1] == 't'){
            if(fase == 2){
                write_double((double)UVS);
                fase++;
            }
            std::vector<float> norm = parse_float(line);
            write_double((double)norm[0]);
            write_double((double)norm[1]);
            //uv
        }
        if(line[0] == 'f' && line[1] == ' '){
            if(fase == 3){
                write_double((double)INDICES);
                fase++;
            }
            std::vector<int> data = parse_faces(line);
            for(int o = 0; o < data.size(); o++){
                if(data[o] != 0){
                    write_int(data[o]);
                }
            }
        }
        if(line[0] == 'x'){
            if(fase == 4){
                println("Ended file process!");
                write_int(END);
                write_int(END);
                write_double((double)INDICES+1.0);
            }
        }
    }
    a.end();
    outputFile.close();

}

void read_bin_f2(const char * file){

    std::vector<float> vertices;
    std::vector<float> normal;
    std::vector<float> uv;

    std::vector<int> face;
    std::vector<float> mesh;

    std::vector<int> norm;
    std::vector<float> normals;

    std::vector<int> uvs;
    std::vector<float> uv_map;

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
                if(*valf == (float)VERTICES){
                    /* println("Vertices start"); */
                    fase++;
                }
                break;
            }
            case 1:{
                //LOADS THE NORMALS
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)NORMALS){
                    /* println("Normals start"); */
                    fase++;
                    break;
                }
                vertices.push_back(*valf);
                break;
            }
            case 2:{
                //LOADS THE UVS
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)UVS){
                    /* println("UVS start"); */
                    fase++;
                    break;
                }
                normal.push_back(*valf);
                break;
            }
            case 3:{
                //LOADS THE INDICES
                valf = reinterpret_cast<float*>(reader4_1);
                if(*valf == (float)INDICES){
                    /* println("Indices start"); */
                    fase++;
                    break;
                }
                uv.push_back(*valf);
                break;
            }
            case 4:{

                if(*vali1 == END){
                }
                vali1 = reinterpret_cast<int*>(reader4_1);
                if(*vali1 != 0 && *vali1 != -1)face.push_back(*vali1);
                
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
void make_bin_f2(const char * filein,const char *fileout){
    Crono a;
    a.start();

    std::vector<float> vertices;
    std::vector<float> normal;
    std::vector<float> uv;
    outputFile = std::ofstream(fileout, std::ios::binary);
    FILE* fp = fopen(filein, "r");
    if(fp == NULL){return;}
    char* line = NULL;
    size_t len = 0;

    int fase = 0;

    while((getline(&line, &len, fp)) != -1){
        if(line[0] == 'v' && line[1] == ' '){
            if(fase == 0){
                write_float((float)VERTICES);
                fase++;
            }
            //vertice
            std::vector<float> pnts = parse_float(line);
            write_float(pnts[0]);
            write_float(pnts[1]);
            write_float(pnts[2]);
        }
        if(line[0] == 'v' && line[1] == 'n'){
            if(fase == 1){
                write_float((float)NORMALS);
                fase++;
            }
            std::vector<float> pnts = parse_float(line);
            write_float((float)pnts[0]);
            write_float((float)pnts[1]);
            write_float((float)pnts[2]);
            //normal
        }
        if(line[0] == 'v' && line[1] == 't'){
            if(fase == 2){
                write_float((float)UVS);
                fase++;
            }
            std::vector<float> norm = parse_float(line);
            write_float((float)norm[0]);
            write_float((float)norm[1]);
            //uv
        }
        if(line[0] == 'f' && line[1] == ' '){
            if(fase == 3){
                write_float((float)INDICES);
                fase++;
            }
            std::vector<int> data = parse_faces(line);
            for(int o = 0; o < data.size(); o++){
                if(data[o] != 0){
                    write_int(data[o]);
                }
            }
        }
        if(line[0] == 'x'){
            println("End reached! with phase: %i", fase);
            if(fase == 4){
                write_int(END);
                write_int(END);
                write_double((double)INDICES+1.0);
                break;
            }
            println("Some errors may have appened");
        }
    }
    a.end();
    outputFile.close();
}


int main(){

    std::string file;
    std::cout << "Nombre (solo): ";
    std::cin >> file;
    
    make_bin_f2(("./scene/models/" + file + ".obj").c_str(), ("scene/compiled/" + file + ".dat").c_str());


    /* outputFile = std::ofstream(DIR, std::ios::binary);

    /* make_bin_f(); *

    write_float(1.871298f);

    outputFile.close(); */

    /* println("%f", (); */

    /* write_float(12386.023f);
    write_float(3.0f/4.0f);
    write_float(1000000.0f);
    write_float(12386.023f*2.0f);

    outputFile.close();

    std::ifstream fin(DIR, std::ios::binary);

    float toread;

    std::vector<float> data;

    while(fin.read(reinterpret_cast<char*>(&toread), sizeof(float))){
        data.push_back(toread);
    }

    for(int i = 0; i < data.size(); i++){
        println("%f", data[i]);
    } */

    //outputFile = std::ofstream(DIR, std::ios::binary);
    //make_bin();    

    //read_bin();

    /* std::ifstream fin(DIR, std::ios::binary);

    double toread;

    std::vector<double> data;

    while(fin.read(reinterpret_cast<char*>(&toread), sizeof(double))){
        data.push_back(toread);
    }

    for(int i = 0; i < data.size(); i++){
        println("%f", data[i]);
    }

    */

    

/*     write_double((double)VERTICES);

    

/* 
    int buffer[] = {0x24, 0xff, 0x33, 0x48}; */

    /* int buffer2[] = {0xff, 0xff, 0xff, 0xff};
    int init_buffer[] = {0x00, 0x00, 0x00, 0xff, 0xad, 0x33, 0x00, 0x00, 0x00};

    write_buffer(&outputFile, init_buffer, 8);
    write_buffer(&outputFile, init_buffer, 8);

    const char * buf2 = "tumadretieneunapollaqueyalaquisierayo";

    for(int i = 0; i < 0xff; i++){
        write_buffer(&outputFile, buf2);
    }
    write_buffer(&outputFile, buffer2, 4); */

    /* outputFile.close(); */

    

/*     int data_a[] = {255, 98, 0x33, 0x48};

    char cc = 0x00;

    for(int i = 0; i < 64; i++){
        cc = data_a[i & 3];
        
    } */

    

    return 0;
}