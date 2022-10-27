#ifndef AENG_READER
#define AENG_READER

#include "util.h"
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <sys/stat.h>

int size(const char *name);
int readfile(const char *name);

inline int size(const char *name){
    struct stat stat_buf;
    int rc = stat(name, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
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

#endif