#ifndef AENG_IMAGE
#define AENG_IMAGE

#define STB_IMAGE_IMPLEMENTATION
#include "../utils/stb_image.h"

struct Image{
    Image(){}
    Image(const char * file);
/*     ~Image(); */

    int width, height, nrChannels;
    unsigned char * data;

    int texture;
};

inline Image::Image(const char * file){
    data = stbi_load(file, &width, &height, &nrChannels, 0);
}

/* inline Image::~Image(){
    stbi_image_free(data);
} */

#endif