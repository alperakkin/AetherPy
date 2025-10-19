#pragma once
#include "game/graphics/color.h"
#include "game/transform.h"
typedef enum
{
    RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_TRIANGLE

} ShapeType;

typedef struct
{
    ShapeType type;
    void *draw;
} RenderComponent;

typedef struct
{
    Vector3 size;
    Color color;

} ShapeRectangle;

RenderComponent *create_rectangle(Vector3 size, Color color);