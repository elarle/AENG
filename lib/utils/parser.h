#ifndef AENG_PARSER
#define AENG_PARSER

#include <string.h>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline vector<string> split ( const string &s, char delim){
    vector<string>result;
    stringstream ss (s);
    string item;

    while ( getline (ss, item, delim)){
        result.push_back(item);
    }
    return result;
};

inline vector<float> parse_float(const char * line){
    vector<float> floats;
    string s = line;
    int len = strlen(line);
    vector<string> v = split(s, ' ');
    for(int i = 1; i < v.size(); i++){
        floats.push_back((float)atof(v[i].c_str()));
    }
    return floats;
};

// ARREGLAR PARSE FACES / TEXTURE COORDS / NORMALS

inline vector<int> parse_faces(const char * line){
    vector<int> res;
    string s = line;
    int len = strlen(line);
    vector<string> v = split(s, ' ');
    for(int i = i; i < (int)v.size(); i++){
        vector<string> vcs = split(v[i], '/');
        for(int e = 0; e < vcs.size(); e++){
            const char * line_v = vcs[e].c_str();
            int val = (int)((float)atof(line_v));
            res.push_back(val);
        }
    }
    return res;
};

#endif