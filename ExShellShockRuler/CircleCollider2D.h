#pragma once


class CirleCollider2D
{
public:
	// Variabels
	Point2 Position;
	float Radius;
	int Layer;

	CirleCollider2D(Point2 position, float radius, int layer)
	{
		this->Position = position;
		this->Radius = radius;
		this->Layer = layer;
	}


};