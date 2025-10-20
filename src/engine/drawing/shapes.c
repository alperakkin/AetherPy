#include "engine/graphics.h"

void draw_rectangle(SDL_Renderer *renderer, GameObject *obj)
{

    if (!obj)
    {
        printf("GameObject Drawing Error");
        return;
    }

    if (!obj->shape)
        return;

    SDL_Rect rect;
    rect.w = (int)obj->shape->size.x;
    rect.h = (int)obj->shape->size.y;
    rect.x = (int)obj->position.x;
    rect.y = (int)obj->position.y;
    SDL_SetRenderDrawColor(renderer,
                           (int)obj->shape->color.R,
                           (int)obj->shape->color.G,
                           (int)obj->shape->color.B,
                           (int)obj->shape->color.A);

    SDL_RenderFillRect(renderer, &rect);
}