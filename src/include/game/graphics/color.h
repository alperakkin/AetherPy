#pragma once
#include <stdlib.h>

typedef struct
{
    int R;
    int G;
    int B;
    int A;
} ColorProp;

ColorProp *CreateColor(int R, int G, int B, int A);