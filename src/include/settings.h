#pragma once
#include "game/graphics/color.h"
#include "libs/utils.h"

typedef struct
{
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    ColorProp background;

} Settings;

extern Settings settings;

void init_settings(char *PATH);