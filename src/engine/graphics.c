#include "engine/graphics.h"

Screen *init_screen(Settings settings)
{

    Screen *screen = malloc(sizeof(Screen));
    screen->width = settings.SCREEN_WIDTH;
    screen->height = settings.SCREEN_HEIGHT;

    Color *background = malloc(sizeof(Color));
    background->R = settings.background.R;
    background->G = settings.background.G;
    background->B = settings.background.B;
    background->A = settings.background.A;

    screen->background = *background;

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

bool draw_gameobject(GameObject *obj, Screen *screen)
{
    if (!obj->shape)
        return true;

    switch (obj->shape->type)
    {
    case RECTANGLE:
    {
        SDL_Rect rect;
        rect.w = (int)obj->shape->size.x;
        rect.h = (int)obj->shape->size.y;
        rect.x = (int)obj->position.x;
        rect.y = (int)obj->position.y;
        SDL_SetRenderDrawColor(screen->renderer,
                               obj->shape->color.R,
                               obj->shape->color.G,
                               obj->shape->color.B,
                               obj->shape->color.A);
        SDL_RenderFillRect(screen->renderer, &rect);
    }

    default:
        break;
    }
    return true;
}

bool draw_objects(Screen *screen)
{
    for (int i = 0; i < object_register.count; i++)
    {
        if (draw_gameobject(object_register.list[i], screen) == false)
            return false;
    }
    return true;
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
                           screen->background.R,
                           screen->background.G,
                           screen->background.B,
                           screen->background.A);

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