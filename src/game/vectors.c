#include <stdlib.h>
#include "vectors.h"

char *Vector3_repr(Vector3 *vector)
{
    if (!vector)
        return NULL;

    char buf[128];
    snprintf(buf, sizeof(buf), "Vector3(x=%f, y=%f, z=%f)",
             (double)vector->x,
             (double)vector->y,
             (double)vector->z);

    return buf;
}

Vector3 *CreateVector3(float x, float y, float z)
{
    Vector3 *c_vec = malloc(sizeof(Vector3));
    c_vec->x = x;
    c_vec->y = y;
    c_vec->z = z;

    return (Vector3 *)c_vec;
}