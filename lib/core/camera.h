#ifndef AENG_CAMERA_H
#define AENG_CAMERA_H

#include <cmath>
#include <math.h>
#include "../utils/globals.h"
#include "../engine/math.h"
#include "../utils/console.h"

struct camera{
    camera();

    float fov = 45.0f;
    float rel = 1.0f;
    float min = 1.0f;
    float max = 100.0f;

    float pitch = 0.0f;
    float yaw = 0.0f;

    float speed = 1.0f;

    vec3 position;
    vec3 rotation;

    vec3 front = vec3(0, 0, -1);
    vec3 up = vec3(0, 1, 0);

    void move(vec2);
    void rotate(vec3);

    void recalc_view();
    void recalc_proj();

    mat4 view;
    mat4 proj;
};

inline camera::camera(){
    recalc_view();
    recalc_proj();
};

inline void camera::recalc_view(){
    //ROT X
    mat4 rxm = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos(rotation.x), sin(rotation.x), 0.0f,
        0.0f, -sin(rotation.x), cos(rotation.x), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 rym = mat4(
        cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin(rotation.y), 0.0f, cos(rotation.y), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 rzm = mat4(
        cos(rotation.z), sin(rotation.z), 0.0f, 0.0f,
        -sin(rotation.z), cos(rotation.z), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    mat4 tf = mat4(
        1.0f, 0.0f, 0.0f, -position.x,
        0.0f, 1.0f, 0.0f, -position.y,
        0.0f, 0.0f, 1.0f, -position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    view = tf * (rym * rxm * rzm);
}

/* inline void camera::recalc_view(){
    //ROT X
    vec3 za = (position - (position + front)).normalize();
    vec3 xa = (up.normalize().cross(za)).normalize();
    vec3 ya = za.cross(xa);

    if(CAM_DEBUG == 1)println(RED, "==============");

    if(CAM_DEBUG == 1)position.print();
    if(CAM_DEBUG == 1)front.print();
    if(CAM_DEBUG == 1)up.print();

    if(CAM_DEBUG == 1)println(YELLOW, "==============");

    if(CAM_DEBUG == 1)xa.print();
    if(CAM_DEBUG == 1)ya.print();
    if(CAM_DEBUG == 1)za.print();

    mat4 rot = mat4(
        xa.x, ya.x, za.x, 0,
        xa.y, ya.y, za.y, 0,
        xa.z, ya.z, za.z, 0,
        0, 0, 0, 1
    );

    mat4 tra = mat4(
        1.0f, 0.0f, 0.0f, -position.x,
        0.0f, 1.0f, 0.0f, -position.y,
        0.0f, 0.0f, 1.0f, -position.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    view = tra * rot;

    if(CAM_DEBUG == 1)println(GREEN, "==============");

    if(CAM_DEBUG == 1)view.print();
} */

inline void camera::recalc_proj(){
    float fov_rad = fov * ((2.0 * 3.141592653589793238462) / 360.0);
    float i = 1.0f / tan(fov_rad/2.0f);
    proj.m[0] = i/(rel);
    proj.m[5] = i;
    proj.m[11] = -1.0f;
    proj.m[10] = -(max + min)/(min - max);
    proj.m[14] = -(2.0f*max*min)/(min - max);
}

inline void camera::move(vec2 dir){
/*     float t = (dir.x * 90.0f)*RAD;
    float t2 = (90.0f + (dir.y * 90.0f))*RAD;

    t+=rotation.x;
    t2+=rotation.y;

    vec3 dirv = vec3(
        sinf(rotation.x+t)*cosf(-rotation.y+t2),
        cosf(rotation.y+t),
        sinf(rotation.x+t)*sinf(-rotation.y+t2)
    ); */

    /* vec3 dirv = vec3(
        cosf(rotation.x+(90.0*RAD))*cosf(rotation.y),
        sinf(rotation.y+(90.0*RAD)),
        sinf(rotation.x+(90.0*RAD))*cosf(rotation.y)
    );

    position = position + (dirv*speed); */

/*     quat v = quat(0, vec3(0.0f, 0.0f, 0.0f));
 */
    quat my = quat(cosf(rotation.x+(dir.x*(180))*RAD*dir.y), 0,(sin(rotation.x+(dir.x*(180))*RAD)*dir.y), 0);
    
    /* quat rot = q * v * q.conjugate(); */

    //ADELANTE
    //position = position + (vec3(sinf(rotation.y+(dir.x*(180))*RAD)*dir.y, (-my.y), cosf(rotation.y+(dir.x*(180))*RAD))*dir.y)*0.05f;

    position = position + (vec3(sinf(rotation.y+(dir.x*(180))*RAD)*dir.y, (-my.y), cosf(rotation.y+(dir.x*(180))*RAD))*dir.y)*0.01f;
    

    //position = position + res;
  
}

/* inline void camera::move(vec2 dir){
    float t = (dir.x * 90.0f)*RAD;
    float t2 = (90.0f + (dir.y * 90.0f))*RAD;

    t+=rotation.x;
    t2+=rotation.y;

    vec3 dirv = vec3(
        sinf(rotation.x+t)*cosf(-rotation.y+t2),
        cosf(rotation.x+t),
        sinf(rotation.x+t)*sinf(-rotation.y+t2)
    );

    position = position + (dirv*speed);

}  */

/* inline void camera::move(vec2 dir){
    

    vec3 dirv = vec3(
        cosf(rotation.x*RAD) * cosf(rotation.y*RAD),
        sinf(rotation.y*RAD),
        sinf(rotation.x*RAD) * cos(pitch*RAD)
    );

    position = position + (dirv*speed);

} */

inline void camera::rotate(vec3 rot){
    this->rotation.x += rot.x*RAD;
    this->rotation.y += rot.y*RAD;
    this->rotation.z += rot.z*RAD;
}

#endif