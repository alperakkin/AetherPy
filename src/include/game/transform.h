#ifndef VECTORS_H
#define VECTORS_H
#include <stdio.h>
typedef struct
{
    float x;
    float y;
    float z;

} Vector3;

Vector3 *CreateVector3(float x, float y, float z);
#endif