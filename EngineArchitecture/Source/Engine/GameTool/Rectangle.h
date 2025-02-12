#pragma once

#include <SDL_rect.h>
#include "Vector/Vector2.h"

struct Rectangle
{
    Rectangle(Vector2 pPosition = Vector2::ZERO, Vector2 pDimensions = Vector2::ONE);

    //functions
    SDL_Rect ToSdlRect() const;

    //AABB Collision Check
    static bool Collision(const Rectangle& a, const Rectangle& b);

    //Operators
    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;

    //variables
    Vector2 position;
    Vector2 dimensions;

    static const Rectangle NullRect;
};


