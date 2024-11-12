#pragma once

#include <SDL_rect.h>
#include "Vector2.h"

struct Rectangle
{
    Rectangle(Vector2 pPosition, Vector2 pDimensions);

    Vector2 position;
    Vector2 dimensions;

    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect
        {
            static_cast< int >( position.x ),
            static_cast< int >( position.y ),
            static_cast< int >( dimensions.x ),
            static_cast< int >( dimensions.y ) 
        };
    }
};


