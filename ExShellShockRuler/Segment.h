#pragma once


class CollisionResult
{
public:
	bool DoesCollide = false;
	Point2 CollisionPoint = Point2(0, 0);
};





class Segment
{
public:
	Point2 Origin = Point2(0, 0);
	Vector2 Vector = Vector2(0, 0);


	// Methodes
	Segment();
	Segment(Point2 origin, Vector2 vector);
	Segment(Point2 origin, Point2 endPoint);
	Segment(Point2 origin, float vecx, float vecy);
	Segment(float x, float y, Vector2 vector);
	Segment(float x, float y, float vecx, float vecy);

	float lenght();

	void set_EndPoint(const Point2& endPoint);
	Point2 get_EndPoint();

	Segment normal();
	Point2 center();
	Segment unit();
	void multiply(const float& multiplyer);

	float getSlope();
	float getOffsetY();
	Point2 getXbyY(const Point2& point);
	Point2 getYbyX(Point2 point);
	
	// Collision
	bool aabbCollide(Segment segment);
	bool onSegment(const Point2& point);
	CollisionResult intersect(Segment segment);
	

	

};