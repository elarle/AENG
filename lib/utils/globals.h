#ifndef AENG_GLOBALS
#define AENG_GLOBALS

#define true 1
#define false 0

#define MAX_FILE_SIZE 2048*8
#define MAX_SHADER_SIZE 2048*8

#define VERTEX_SHADER "./shaders/VSN.glsl"
#define FRAGMENT_SHADER "./shaders/FSN.glsl"

#define MAX_SHADER_LOG_SIZE 2048

#define LOG_INFO 1
#define LOG_WARNING 2
#define LOG_ERROR 3
#define LOG_NOINDENT 4

#define MAX_FPS 144.0
#define TPS_BASE 128.0

#define CAM_DEBUG 0
#define OGL_DEBUG 0
#define DEBUG 1

#define VSync 0

#define ANTIALIAS_LEVEL 0x10

#define CAM_SENS 0.092

//-----------MATH-----------//

#define PI 3.141592653589793238462

#define RAD PI / 180.0
#define DEG 180.0 / PI

#endif