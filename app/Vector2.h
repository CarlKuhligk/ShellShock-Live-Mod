#pragma once

class Point2;

typedef enum Direction
{
	LEFT = -1,
	RIGHT = 1,
	ZERO = 0
};


class Vector2
{
	// Variabels
public:
	float X = 0;
	float Y = 0;

	// Methodes
	Vector2();
	Vector2(float x, float y);


	Vector2 operator+(const Vector2 &vector);
	Vector2 operator+=(const Vector2 &vector);

	Vector2 operator-(const Vector2 &vector);
	Vector2 operator-=(const Vector2 &vector);

	Vector2 operator*(const float &multiplyer);
	Vector2 operator*=(const float &multiplyer);

	void operator=(const Vector2 &vector);

	float lenght();

	float cross(const Vector2 &vector);
	float dot(const Vector2 &vector);

	Direction direction(const Vector2& vector);
	
};
