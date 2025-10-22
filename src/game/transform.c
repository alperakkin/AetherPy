#include <stdlib.h>
#include "game/transform.h"

Vector3Prop *CreateVector3Prop(float x, float y, float z)
{
    Vector3Prop *c_vec = malloc(sizeof(Vector3Prop));
    c_vec->x = x;
    c_vec->y = y;
    c_vec->z = z;

    return (Vector3Prop *)c_vec;
}