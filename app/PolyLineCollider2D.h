#pragma once

class PolyLineCollider2D
{

private:
	// Variabels
	std::vector<Point2> points_ = {};
	std::vector<Segment> lines_ = {};
public:
	// Readonly
	std::vector<Point2>& Points;
	std::vector<Segment>& Lines;

	// Variabels
	int Layer;

	// Methodes
	PolyLineCollider2D(int layer);
	PolyLineCollider2D(std::vector<Point2> points, int layer);

	void addPoint(const Point2& point);
	void addLine(const Segment& segment);
	void clear();

	CollisionResult Collide(const LineCollider2D& LineCollider);
	//CollisionResult Collide(const PolyLineCollider2D& PolyLineCollider);


};