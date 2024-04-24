#include "IncludeHead.h"


//__________Vector2__________
// Methodes
Vector2::Vector2()
{
}

Vector2::Vector2(float x, float y)
{
	this->X = x;
	this->Y = y;
}

#pragma region Add-Operation
Vector2 Vector2::operator+(const Vector2 &vector)
{
	return Vector2(X + vector.X, Y + vector.Y);
}

Vector2 Vector2::operator+=(const Vector2 &vector)
{
	return Vector2(X += vector.X, Y += vector.Y);
}
#pragma endregion

#pragma region Substract-Operation
Vector2 Vector2::operator-(const Vector2 &vector)
{
	return Vector2(X - vector.X, Y - vector.Y);
}

Vector2 Vector2::operator-=(const Vector2 &vector)
{
	return Vector2(X -= vector.X, Y -= vector.Y);
}
#pragma endregion

#pragma region MultiplY-Operation
Vector2 Vector2::operator*(const float &multiplyer)
{
	return Vector2(X * multiplyer, Y * multiplyer);
}

Vector2 Vector2::operator*=(const float &multiplyer)
{
	return Vector2(X *= multiplyer, Y *= multiplyer);
}
#pragma endregion


void Vector2::operator=(const Vector2 &vector)
{
	X = vector.X;
	Y = vector.Y;
}

float Vector2::lenght()
{
	return sqrt(X * X + Y * Y);
}

float Vector2::cross(const Vector2 &vector)
{
	return X * vector.Y - Y * vector.X;
}

float Vector2::dot(const Vector2 &vector)
{
	return X * vector.X + Y * vector.Y;
}


Direction Vector2::direction(const Vector2& vector)
{
	int cross_product;
	if (true)
	{
		cross_product = X * vector.Y - Y * vector.X;
	}


	// return RIGHT if cross product is positive
	if (cross_product > 0)
		return RIGHT;

	// return LEFT if cross product is negative
	if (cross_product < 0)
		return LEFT;

	// return ZERO if cross product is zero. 
	return ZERO;
}

