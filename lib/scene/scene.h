#ifndef AENG_SCENE_MANAGER
#define AENG_SCENE_MANAGER

#include "../core/object.h"

#include <vector>
struct Scene{

    const char * working_directory;

    Scene();
    Scene(const char * filename){
        working_directory = filename;
    }

    std::vector<object> objs;

    void load(){}

};

#endif