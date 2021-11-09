#pragma once

class PolyLineCollider2D;

class LineCollider2D
{
private:
	// Variabels
	Point2 p1_, p2_;

public:
	// ReadOnly
	const Point2& P1, P2;

	// Variabels
	Segment Line;
	int Layer;

	// Methodes
	LineCollider2D(int layer);
	LineCollider2D(Segment segment, int layer = -1);
	LineCollider2D(Point2 point, Vector2 vector, int layer = -1);
	LineCollider2D(const Point2& point1, const Point2& point2, int layer = -1);
	LineCollider2D(const float& x1, const float& y1, const float& x2, const float& y2, int layer = -1);

	void set_Line();
	void set_Layer(int layer);


	CollisionResult Collide(const LineCollider2D& LineCollider);
	CollisionResult Collide(const PolyLineCollider2D& PolyLineCollider);



};