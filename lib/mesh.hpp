#ifndef AENG_MESH_H
#define AENG_MESH_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include "console.hpp"

inline std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}
std::vector<float> parse_float(const char *line);
inline std::vector<float> parse_float(const char *line){
    std::vector<float> floats;
    std::string s = line;
        int len = strlen(line);
        std::vector<std::string> v = split(s, ' ');
        for(int i = 1; i < v.size(); i++){
            floats.push_back((float)atof(v[i].c_str()));
        }
    return floats;
}
std::vector<int> parse_faces(const char *line);
inline std::vector<int> parse_faces(const char *line){
    std::vector<int> floats;
    std::string s = line;
        int len = strlen(line);
        std::vector<std::string> v = split(s, ' ');
        for(int i = 1; i < (int)v.size(); i++){
            
                //floats.push_back((int)atof(v[i].c_str()));

            std::vector<std::string> vcs = split(v[i], '/');

            for(int e = 0; e < vcs.size(); e+=3){
                const char *line_var = vcs[e].c_str();
                int value = (int)((float)atof(line_var));
                //printf("VAR: %s -> %i | ", line_var, value);
                floats.push_back(value);
            }
        }
    return floats;
}

#endif