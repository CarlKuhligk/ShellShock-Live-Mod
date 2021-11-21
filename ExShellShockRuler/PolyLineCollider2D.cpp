#include "IncludeHead.h"

PolyLineCollider2D::PolyLineCollider2D(int layer) : Points(points_), Lines(lines_)
{
	Layer = layer;
	clear();
}

PolyLineCollider2D::PolyLineCollider2D(std::vector<Point2> points, int layer) : Points(points_), Lines(lines_)
{
	Layer = layer;
	clear();
}


void PolyLineCollider2D::addPoint(const Point2& point)
{
	points_.push_back(point);
	if (points_.size() > 1)
	{
		// add linesegment
		addLine(Segment(points_[points_.size() - 2], point));
	}
}

void PolyLineCollider2D::addLine(const Segment& segment)
{
	lines_.push_back(segment);
}

void PolyLineCollider2D::clear()
{
	points_.clear();
	lines_.clear();
}


CollisionResult PolyLineCollider2D::Collide(const LineCollider2D& LineCollider)
{
	// Layercheck
	if (CollideMatrix[Layer][LineCollider.Layer] == true)
	{
		for (int i = 0; i < lines_.size(); i++)
		{
			CollisionResult result = lines_[i].intersect(LineCollider.Line);
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