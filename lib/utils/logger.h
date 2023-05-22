#ifndef AENG_LOGGER
#define AENG_LOGGER

#include "globals.h"
#include <bits/types/FILE.h>
#include <bits/types/time_t.h>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

//#define bool int

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
        case LOG_NOINDENT:
            return (char*)"\t";
    }
    return (char*)"[UNKNOWN] ";
}
inline void log_shader(const char * msg){
    FILE* file = fopen(LOG_FILE, "a");
    if(!file){return;}

    std::stringstream ss;

    ss << log_type(LOG_NOINDENT);
    ss << "Shader error: \n\t";
    ss << msg;
    ss << "\n";

    fclose(file);

    return;

}
void log(int type, const char* msg, ...);
inline void log(int type, const char* msg,...){
    va_list s_args;
    FILE* file = fopen(LOG_FILE, "a");
    if(!file){return;}
    va_start(s_args, msg);
    std::string append;

    std::ostringstream ss;

    /* ss << log_type(type) << std::format(msg, s_args) << '\n'; */
    
    append = log_type(type);
    append += msg;
    append += '\n'; 

    vfprintf(file, append.c_str(), s_args);
    va_end(s_args);
    fclose(file);
    return;
}

#endif