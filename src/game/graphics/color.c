#include "game/graphics/color.h"

ColorProp *CreateColor(int R, int G, int B, int A)
{
    ColorProp *c_color = malloc(sizeof(ColorProp));
    c_color->R = R;
    c_color->G = G;
    c_color->B = B;
    c_color->A = A;

    return (ColorProp *)c_color;
}