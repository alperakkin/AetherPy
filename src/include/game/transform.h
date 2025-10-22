#ifndef VECTORS_H
#define VECTORS_H
#include <stdio.h>
typedef struct
{
    float x;
    float y;
    float z;

} Vector3Prop;

Vector3Prop *CreateVector3Prop(float x, float y, float z);
#endif