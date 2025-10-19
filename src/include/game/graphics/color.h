#pragma once
#include <stdlib.h>

typedef struct
{
    int R;
    int G;
    int B;
    int A;
} Color;

Color *CreateColor(int R, int G, int B, int A);