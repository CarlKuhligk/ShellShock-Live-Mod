#pragma once

class Vector2;

class Point2
{
public:
	float X = 0;
	float Y = 0;

	// Methodes
	Point2() {};
	Point2(float x, float y);

	Point2 operator+(const Vector2 &vector);
	Point2 operator+=(const Vector2 &vector);
	Point2 operator-(const Vector2 &vector);
	Point2 operator-=(const Vector2 &vector);

	Vector2 operator-(const Point2& point);

	void operator=(const Point2 &point);

};
