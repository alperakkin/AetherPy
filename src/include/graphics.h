#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "settings.h"
#include "game_types.h"
#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    Color background;
} Screen;

Screen *init_screen(Settings settings);
bool render(Screen *screen);
void destroy_screen(Screen *screen);