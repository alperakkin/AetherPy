#include <stdlib.h>
#include "transform.h"

Vector3 *CreateVector3(float x, float y, float z)
{
    Vector3 *c_vec = malloc(sizeof(Vector3));
    c_vec->x = x;
    c_vec->y = y;
    c_vec->z = z;

    return (Vector3 *)c_vec;
}