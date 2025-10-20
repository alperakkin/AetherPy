#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game/graphics/color.h"
#include "game/scene.h"
#include "settings.h"

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

bool draw_gameobject(Screen *screen, GameObject *obj);
bool draw_objects(Screen *screen);

void draw_rectangle(SDL_Renderer *renderer, GameObject *obj);

Screen *init_screen(Settings settings);
bool render(Screen *screen);
void destroy_screen(Screen *screen);
bool draw_objects(Screen *screen);
bool draw_gameobject(Screen *screen, GameObject *obj);