#ifndef AENG_LIGHT
#define AENG_LIGHT

#include "../engine/math.h"

struct light{
    vec4 color;
    vec3 pos;
    vec3 dir;
};

#endif