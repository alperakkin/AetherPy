#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include "game/graphics/color.h"
#include "game/scene.h"
#include "game/game.h"
#include "settings.h"
#include "engine/input_controls.h"

typedef struct
{
    int width;
    int height;
    ColorProp background;
} Screen;

bool draw_gameobject(Screen *screen, GameObject *obj);
bool draw_objects(Screen *screen);

Screen *init_screen();
void init_pause_frame(Screen *screen);
bool render(Screen *screen);
void destroy_screen(Screen *screen);
bool draw_objects(Screen *screen);
bool draw_gameobject(Screen *screen, GameObject *obj);
void draw_rectangle(GameObject *obj);
void draw_circle(GameObject *obj);
void draw_text(GameObject *obj);