#ifndef VECTORS_H
#define VECTORS_H
#include <stdio.h>
typedef struct
{
    float x;
    float y;
    float z;

} Vector3;

char *Vector3_repr(Vector3 *vector);
Vector3 *CreateVector3(float x, float y, float z);
#endif