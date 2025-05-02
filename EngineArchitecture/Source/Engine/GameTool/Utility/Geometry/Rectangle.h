#pragma once

#include <SDL_rect.h>
#include "Engine/GameTool/Utility/Vector/Vector2.h"

/*
 Represents a 2D axis-aligned rectangle used for UI, collision detection, or rendering.
 Supports AABB collision checks and conversion to SDL's rectangle format.
 */
struct Rectangle
{
    /*
     * Constructor for Rectangle.
     * @param pPosition The top-left position of the rectangle (default: Vector2::ZERO).
     * @param pDimensions The width and height of the rectangle (default: Vector2::ONE).
     */
    Rectangle(Vector2 pPosition = Vector2::ZERO, Vector2 pDimensions = Vector2::ONE);

    //Functions
     /*
     * Converts the rectangle to an SDL_Rect structure for rendering or input detection.
     * @return SDL_Rect equivalent of this rectangle.
     */
    SDL_Rect ToSdlRect() const;

    /*
     * Checks for AABB (Axis-Aligned Bounding Box) collision between two rectangles.
     * @param a The first rectangle.
     * @param b The second rectangle.
     * @return True if the rectangles overlap, false otherwise.
     */
    static bool Collision(const Rectangle& a, const Rectangle& b);

    //Operators
    bool operator==(const Rectangle& other) const;
    bool operator!=(const Rectangle& other) const;

    //variables
    Vector2 position; // Top-left corner of the rectangle.
    Vector2 dimensions; // Width (x) and height (y) of the rectangle.

    static const Rectangle NullRect; // A predefined rectangle with zero size and position.
};


