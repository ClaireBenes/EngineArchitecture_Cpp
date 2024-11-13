#include "Rectangle.h"

Rectangle::Rectangle(Vector2 pPosition, Vector2 pDimensions)
{
	position = pPosition;
	dimensions = pDimensions;
}

bool Collision(Rectangle& a, Rectangle& b)
{
	int xMinA = a.position.x;
	int yMinA = a.position.y;
	int xMaxA = a.position.x + a.dimensions.x;
	int yMaxA = a.position.y + a.dimensions.y;

	int xMinB = b.position.x;
	int yMinB = b.position.y;
	int xMaxB = b.position.x + b.dimensions.x;
	int yMaxB = b.position.y + b.dimensions.y;

	return ( !( xMinB > xMaxA || yMinB > yMaxA
		|| xMaxB < xMinA || yMaxB < yMinA ) );
}
