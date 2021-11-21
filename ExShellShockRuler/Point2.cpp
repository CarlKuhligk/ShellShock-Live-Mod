#include "IncludeHead.h"




Point2::Point2(float x, float y)
{
	this->X = x;
	this->Y = y;
}

#pragma region Add-Operation
Point2 Point2::operator+(const Vector2 &vector)
{
	return Point2(X + vector.X, Y + vector.Y);
}

Point2 Point2::operator+=(const Vector2 &vector)
{
	return Point2(X += vector.X, Y += vector.Y);
}
#pragma endregion

#pragma region Subtract-Operation
Point2 Point2::operator-(const Vector2 &vector)
{
	return Point2(X - vector.X, Y - vector.Y);
}

Point2 Point2::operator-=(const Vector2 &vector)
{
	return Point2(X -= vector.X, Y -= vector.Y);
}
#pragma endregion


Vector2 Point2::operator-(const Point2& point)
{
	return Vector2(X - point.X, Y - point.Y);
}


void Point2::operator=(const Point2 &point)
{
	this->X = point.X;
	this->Y = point.Y;
}





