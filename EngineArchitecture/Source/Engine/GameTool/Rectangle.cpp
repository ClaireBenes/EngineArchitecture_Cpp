#include "Rectangle.h"

const Rectangle Rectangle::NullRect({ 0.0f,0.0f }, { 0.0f,0.0f });

Rectangle::Rectangle(Vector2 pPosition, Vector2 pDimensions)
{
	position = pPosition;
	dimensions = pDimensions;
}

//cast our rectangle to SDL rectangle
SDL_Rect Rectangle::ToSdlRect() const
{
	return SDL_Rect
	{
		static_cast< int >( position.x ),
		static_cast< int >( position.y ),
		static_cast< int >( dimensions.x ),
		static_cast< int >( dimensions.y )
	};

}

//AABB Collision calculation
bool Rectangle::Collision(const Rectangle& a, const Rectangle& b)
{
	float xMinA = a.position.x;
	float yMinA = a.position.y;
	float xMaxA = a.position.x + a.dimensions.x;
	float yMaxA = a.position.y + a.dimensions.y;

	float xMinB = b.position.x;
	float yMinB = b.position.y;
	float xMaxB = b.position.x + b.dimensions.x;
	float yMaxB = b.position.y + b.dimensions.y;

	/*return ( !( xMinB > xMaxA || yMinB > yMaxA
		|| xMaxB < xMinA || yMaxB < yMinA ) );*/
	return ( xMinA < xMaxB ) && ( xMaxA > xMinB ) && ( yMinA < yMaxB ) && ( yMaxA > yMinB );
}

// ==
bool Rectangle::operator==(const Rectangle& other) const
{
	return position.x == other.position.x &&
		position.y == other.position.y &&
		dimensions.x == other.dimensions.x &&
		dimensions.y == other.dimensions.y;
}

// !=
bool Rectangle::operator!=(const Rectangle& other) const
{
	return !(*this == other);
}
