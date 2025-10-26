#pragma once
#include <stdbool.h>

typedef struct
{
    bool paused;
} GameState;

extern GameState game_state;
