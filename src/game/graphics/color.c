#include "game/graphics/color.h"

Color *CreateColor(int R, int G, int B, int A)
{
    Color *c_color = malloc(sizeof(Color));
    c_color->R = R;
    c_color->G = G;
    c_color->B = B;
    c_color->A = A;

    return (Color *)c_color;
}