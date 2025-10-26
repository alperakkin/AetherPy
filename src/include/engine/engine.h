#pragma once
#include <time.h>
#include <stdbool.h>
#include "libs/utils.h"
#include "libs/scripting.h"
#include "engine/graphics.h"
#include "game/game.h"
void run(char *PATH);
void load_modules(FileList fl);
void start();
void setup();
void update();
void game_loop();