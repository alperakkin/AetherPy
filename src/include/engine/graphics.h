#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include "game/graphics/color.h"
#include "game/scene.h"
#include "game/game.h"
#include "settings.h"
#include "engine/input_controls.h"

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

typedef struct
{
    int width;
    int height;
    ColorProp background;
} Screen;

bool draw_gameobject(Screen *screen, GameObject *obj);
bool draw_objects(Screen *screen);

Screen *init_screen(Settings settings);
void init_pause_frame(Screen *screen);
bool render(Screen *screen);
void destroy_screen(Screen *screen);
bool draw_objects(Screen *screen);
bool draw_gameobject(Screen *screen, GameObject *obj);
void draw_rectangle(GameObject *obj);
void draw_circle(GameObject *obj);
void draw_text(GameObject *obj);