#ifndef AENG_UTILS
#define AENG_UTILS

#include <bits/types/FILE.h>
#include <bits/types/time_t.h>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

//#define bool int
#define true 1
#define false 0

#define MAX_FILE_SIZE 2048
#define MAX_SHADER_SIZE 2048

#define LOG_INFO 1
#define LOG_WARNING 2
#define LOG_ERROR 3

#define ANTIALIAS_LEVEL 0x10

#define LOG_FILE "./engine.log"

int log_start();
inline int log_start(){
    time_t now;
    char* date;
    FILE* file = fopen( LOG_FILE, "w");
    if (!file) return false;
    now = time( NULL );
    date = ctime(&now);

    fprintf( file, "Starting Engine. Local time %s", date);
    fprintf(file, "Build version: %s %s\n\n", __DATE__, __TIME__);
    fclose(file);
    return true;
}
char* log_type(int type);
inline char* log_type(int type){
    switch (type) {
        case LOG_INFO:
            return (char*)"[INFO] ";
        case LOG_WARNING:
            return (char*)"[WARNING] ";
        case LOG_ERROR:
            return (char*)"[ERROR] ";
    }
    return (char*)"[UNKNOWN] ";
}
void log(int type, const char* msg, ...);
inline void log(int type, const char* msg,...){
    va_list s_args;
    FILE* file = fopen(LOG_FILE, "a");
    if(!file){return;}
    va_start(s_args, msg);
    std::string append;
    
    append = log_type(type);
    append += msg;
    append += '\n';
    
    vfprintf(file, append.c_str(), s_args);
    va_end(s_args);
    fclose(file);
    return;
}

#endif