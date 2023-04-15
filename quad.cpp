#include <cstdio>
#include <math.h>

#define PI 3.141592653589793238462

#define RAD PI / 180.0
#define DEG 180.0 / PI

struct quat{
    quat();
    quat(float, float, float, float);
    float x;
    float y;
    float z;
    float w;
    
    quat operator*(const quat& q);
};

quat::quat(float W, float X, float Y, float Z){
    this->x = X;
    this->y = Y;
    this->z = Z;
    this->w = W;
}

quat quat::operator*(const quat &q){
    return quat(
        (w*q.w)-(x*q.x)-(y*q.y)-(z*q.z),
        (x*q.w)+(w*q.x)+(y*q.z)-(z*q.y),
        (y*q.w)+(w*q.y)+(z*q.x)-(x*q.z),
        (z*q.w)+(w*q.z)+(x*q.y)-(y*q.x)
    );
}

int main(){

    float deg = (45.0f * RAD)/2;

    float x = 0;
    float y = 1;
    float z = 0;

    float px = 5.0f;
    float py = 2.0f;
    float pz = 3.0f;

    quat q = quat(cosf(deg), (sin(deg)*(x)),(sin(deg)*(y)), (sin(deg)*(z)));
    quat qc = quat(cosf(deg), -(sin(deg)*(x)),-(sin(deg)*(y)), -(sin(deg)*(z)));

    quat v = quat(0, px, py, pz);

    quat r = q * v * qc;

    printf("X:%f, Y:%f, Z:%f | W:%f", r.x, r.y, r.z, r.w);

    return 0;
}