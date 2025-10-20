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

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Graphics could not be initialized! SDL_Error: %s\n",
               SDL_GetError());
        return NULL;
    }

    screen->window = SDL_CreateWindow(
        "Aether",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screen->width, screen->height,
        SDL_WINDOW_SHOWN);
    if (!screen->window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        destroy_screen(screen);
        return NULL;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
    if (!screen->renderer)
    {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        destroy_screen(screen);
        return NULL;
    }

    return screen;
}

bool render(Screen *screen)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return false;
    }
    SDL_SetRenderDrawColor(screen->renderer,
                           (int)screen->background.R,
                           (int)screen->background.G,
                           (int)screen->background.B,
                           (int)screen->background.A);

    SDL_RenderClear(screen->renderer);

    if (draw_objects(screen) == false)
        return false;

    SDL_RenderPresent(screen->renderer);

    return true;
}
void destroy_screen(Screen *screen)
{
    if (screen && screen->renderer)
        SDL_DestroyRenderer(screen->renderer);

    if (screen && screen->window)
        SDL_DestroyWindow(screen->window);
    SDL_Quit();
    free(screen);
}