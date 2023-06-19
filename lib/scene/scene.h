#ifndef AENG_SCENE_MANAGER
#define AENG_SCENE_MANAGER

#include "../core/object.h"

#include <vector>
#include <fstream>

/* void gen_uint32(char * a){
    uint32_t res;
    uint8_t a1 = (uint8_t)*a;
    uint8_t a2 = (uint8_t)*a;
    uint8_t b1 = (uint8_t)*a;
    uint8_t b2 = (uint8_t)*a;
    res |= a1;
    res <<= 8;
    res |= a2;
    res <<= 8;
    res |= b1;
    res <<= 8;
    res |= b2;
    std::cout << "res = " << res; 
} */

struct Scene{

    const char * working_directory;

    Scene();
    Scene(const char * filename){
        working_directory = filename;
    }

    std::vector<object> objs;


    void load(){

        

        /* std::ofstream outputFile(working_directory, std::ios::binary);
        uint32_t size = 0xaaffad33;
        outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
        outputFile.close();

        std::ifstream inputFile(working_directory, std::ios::binary);

        char byte[4];

        inputFile.get(byte[0]);
        inputFile.get(byte[1]);
        inputFile.get(byte[2]);
        inputFile.get(byte[3]);
        
        inputFile.close();

        gen_uint32(byte); 

       
        int f_size = filesize(working_directory);
        char * raw = new char[f_size];

        readfile(working_directory, raw);

        println(RED, "\n################");

        for(int a = 0; a < f_size; a++){
            print(RED, "0x%02X ", static_cast<unsigned char>(raw[a]));
        }

        println(RED, "\n################"); */
    }


};

#endif