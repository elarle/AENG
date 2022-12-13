#ifndef AENG_DTEXT
#define AENG_DTEXT

#include "draw_text.hpp"
#include "math.hpp"

DMI dmi; 

void dtext_init(){
    vec3 vert[] = {
        vec3(-1.0f,1.0f,0.0f),
        vec3(1.0f,1.0f,0.0f),
        vec3(-1.0f,-1.0f, 0.0f),
        vec3(1.0f,-1.0f,0.0f),
        vec3(1.0f,1.0f,0.0f),
        vec3(-1.0f,1.0f,0.0f)
    };
    
}

#endif