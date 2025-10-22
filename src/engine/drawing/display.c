#include "engine/graphics.h"

#include "settings.h"
Screen *init_screen(Settings settings)
{

    Screen *screen = malloc(sizeof(Screen));
    screen->width = settings.SCREEN_WIDTH;
    screen->height = settings.SCREEN_HEIGHT;

    screen->background.R = settings.background.R;
    screen->background.G = settings.background.G;
    screen->background.B = settings.background.B;
    screen->background.A = settings.background.A;
    SetTraceLogLevel(LOG_NONE);
    InitWindow(screen->width, screen->height, "Aether Game Engine");

    return screen;
}

bool render(Screen *screen)
{

    if (WindowShouldClose())
        return false;

    BeginDrawing();
    ClearBackground((Color){
        screen->background.R,
        screen->background.G,
        screen->background.B,
        screen->background.A,
    });

    if (draw_objects(screen) == false)
        return false;
    EndDrawing();
    return true;
}
void destroy_screen(Screen *screen)
{
    if (screen)
        CloseWindow();
    free(screen);
}