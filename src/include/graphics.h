#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
} Screen;

Screen *init_screen();
bool render(Screen *screen);
void destroy_screen(Screen *screen);