#include "IncludeHead.h"


// Metohdes
LineCollider2D::LineCollider2D(int layer) : P1(p1_), P2(p2_)
{
	this->Layer = layer;
}

LineCollider2D::LineCollider2D(Segment segment, int layer) : P1(p1_), P2(p2_)
{
	p1_ = segment.Origin;
	p2_ = segment.get_EndPoint();
	set_Line();
	set_Layer(layer);
}

LineCollider2D::LineCollider2D(Point2 point, Vector2 vector, int layer) : P1(p1_), P2(p2_)
{
	p1_ = point;
	p2_ = point + vector;
	set_Line();
	set_Layer(layer);
}
LineCollider2D::LineCollider2D(const Point2& point1, const Point2& point2, int layer) : P1(p1_), P2(p2_)
{
	p1_ = point1;
	p2_ = point2;
	set_Line();
	set_Layer(layer);
}
LineCollider2D::LineCollider2D(const float& x1, const float& y1, const float& x2, const float& y2, int layer) : P1(p1_), P2(p2_)
{
	p1_ = Point2(x1, y1);
	p2_ = Point2(x2, y2);
	set_Line();
	set_Layer(layer);
}

void LineCollider2D::set_Line()
{
	Line = Segment(p1_, p2_);
}

void LineCollider2D::set_Layer(int layer)
{
	if (layer >= 0) this->Layer = layer;
}


CollisionResult LineCollider2D::Collide(const LineCollider2D& LineCollider)
{
	// Layercheck
	if (CollideMatrix[Layer][LineCollider.Layer] == true)
	{
		// can collide 
		return Line.intersect(LineCollider.Line);
	}
	// no collision
	return CollisionResult();
}

CollisionResult LineCollider2D::Collide(const PolyLineCollider2D& PolyLineCollider)
{
	// Layercheck
	if (CollideMatrix[Layer][PolyLineCollider.Layer] == true)
	{
		for (int i = 0; i < PolyLineCollider.Lines.size(); i++)
		{
			CollisionResult result = Line.intersect(PolyLineCollider.Lines[i]);
			if (result.DoesCollide == true)
			{
				// collision
				return result;
			}
		}
	}
	// no collision
	return CollisionResult();
}
