#include "engine/graphics.h"

void draw_rectangle(SDL_Renderer *renderer, GameObject *obj)
{
    if (!obj)
    {
        printf("GameObject Drawing Error");
        return;
    }
    SDL_Rect rect;
    rect.w = (int)obj->shape->size.x;
    rect.h = (int)obj->shape->size.y;
    rect.x = (int)obj->position.x;
    rect.y = (int)obj->position.y;
    SDL_SetRenderDrawColor(renderer,
                           obj->shape->color.R,
                           obj->shape->color.G,
                           obj->shape->color.B,
                           obj->shape->color.A);

    SDL_RenderFillRect(renderer, &rect);
}