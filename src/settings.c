#include "settings.h"
Settings settings;

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

void init_settings(char *PATH)
{

    ColorProp color;
    color.R = 0;
    color.G = 0;
    color.B = 0;
    color.A = 0;

    settings.SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
    settings.SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;
    settings.background = color;
    get_settings(PATH);
}