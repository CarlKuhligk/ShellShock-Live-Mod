#include "IncludeHead.h"

Segment::Segment()
{

}

Segment::Segment(Point2 origin, Vector2 vector)
{
	this->Origin = origin;
	this->Vector = vector;
}
Segment::Segment(Point2 origin, Point2 endPoint)
{
	this->Origin = origin;
	set_EndPoint(endPoint);
}
Segment::Segment(Point2 origin, float vecx, float vecy)
{
	this->Origin = origin;
	this->Vector = Vector2(vecx, vecy);
}
Segment::Segment(float x, float y, Vector2 vector)
{
	Origin = Point2(x, y);
	this->Vector = vector;
}
Segment::Segment(float x, float y, float vecx, float vecy)
{
	Origin = Point2(x, y);
	Vector = Vector2(vecx, vecy);
}



float Segment::lenght()
{
	float dx = Origin.X - Origin.X + Vector.X;
	float dy = Origin.Y - Origin.Y + Vector.Y;
	return sqrt(dx * dx + dy * dy);
}

void Segment::set_EndPoint(const Point2& endPoint)
{
	Vector.X = endPoint.X - Origin.X;
	Vector.Y = endPoint.Y - Origin.Y;
}


Point2 Segment::get_EndPoint()
{
	return Point2(Origin.X + Vector.X, Origin.Y + Vector.Y);
}

Segment Segment::normal()
{
	float x1 = Origin.Y;
	float y1 = Origin.X + Vector.X;
	float x2 = Origin.Y + Vector.Y;
	float y2 = Origin.X;

	return Segment(x1, y1, x2 - x1, y2 - y1);
}


Point2 Segment::center()
{
	float _x = Origin.X + Origin.X + Vector.X;
	float _y = Origin.Y + Origin.Y + Vector.Y;
	_x /= 2;
	_y /= 2;
	return Point2(_x, _y);
}

Segment Segment::unit()
{
	float lenght = this->lenght();
	return Segment(0, 0, Origin.X / lenght, Origin.Y / lenght);
}

void Segment::multiply(const float& multiplyer)
{
	Vector *= multiplyer;
}

float Segment::getSlope()
{
	Point2 endPoint = get_EndPoint();
	return (endPoint.Y - Origin.Y) / (endPoint.X - Origin.X);
}

float Segment::getOffsetY()
{
	float m = getSlope();
	return Origin.Y - m * Origin.X;
}

Point2 Segment::getXbyY(const Point2& point)
{
	float m = getSlope();
	float n = getOffsetY();
	return Point2((point.Y - n) / m, point.Y);
}

Point2 Segment::getYbyX(Point2 point)
{
	float m = getSlope();
	float n = getOffsetY();
	return Point2(point.X, m * point.X + n);
}



bool Segment::aabbCollide(Segment segment)
{
	// AABB-Collisioncheck
	bool collision = false;
	// collision x-axis?
	bool collisionX = false;
	if (Vector.X >= 0 && segment.Vector.X >= 0)
	{
		collisionX = (get_EndPoint().X >= segment.Origin.X) && (segment.get_EndPoint().X >= Origin.X);
	}
	else if (Vector.X >= 0 && segment.Vector.X <= 0)
	{
		collisionX = (get_EndPoint().X >= segment.get_EndPoint().X) && (segment.Origin.X >= Origin.X);
	}

	else if (Vector.X <= 0 && segment.Vector.X >= 0)
	{
		collisionX = (Origin.X >= segment.Origin.X) && (segment.get_EndPoint().X >= get_EndPoint().X);
	}
	else if (Vector.X <= 0 && segment.Vector.X <= 0)
	{
		collisionX = (Origin.X >= segment.get_EndPoint().X) && (segment.Origin.X >= get_EndPoint().X);
	}




	// collision y-axis?
	bool collisionY = false;
	if (Vector.Y >= 0 && segment.Vector.Y >= 0)
	{
		collisionY = (get_EndPoint().Y  >= segment.Origin.Y) && (segment.get_EndPoint().Y >= Origin.Y);
	}
	else if (Vector.Y > 0 && segment.Vector.Y < 0)
	{
		collisionY = (get_EndPoint().Y >= segment.get_EndPoint().Y) && (segment.Origin.Y >= Origin.Y);
	}

	else if (Vector.Y <= 0 && segment.Vector.Y >= 0)
	{
		collisionY = (Origin.Y >= segment.Origin.Y) && (segment.get_EndPoint().Y >= get_EndPoint().Y);
	}
	else if(Vector.Y <= 0 && segment.Vector.Y <= 0)
	{
		collisionY = (Origin.Y >= segment.get_EndPoint().Y) && (segment.Origin.Y >= get_EndPoint().Y);
	}

	// collision possible only if both axes overlap
	collision = collisionX && collisionY;
	return collision;
}

bool Segment::onSegment(const Point2& point)
{
	bool A = min(Origin.X, get_EndPoint().X) <= point.X <= max(Origin.X, get_EndPoint().X);
	bool B = min(Origin.Y, get_EndPoint().Y) <= point.Y <= max(Origin.Y, get_EndPoint().Y);
	if ( A && B)
	{
		return true;
	}
	else
	{
		//std::cout << "Segment x: " << Origin.X << " y: " << Origin.Y <<
		//				"  Vect x: " << Vector.X << " y: " << Vector.Y <<
		//				"  Point: x: " << point.X << " y: " << point.Y << 
		//				" A: " << A << " B: " << B << "\n";
		return false;
	}
}



CollisionResult Segment::intersect(Segment segment)
{
	// Result
	CollisionResult result;

	if (aabbCollide(segment) == true)
	{
		// Collisioncheck by directions
		// Calculate the direction of the point based on the vector
		int dir1 = Vector.direction(Origin - segment.Origin);
		int dir2 = Vector.direction(Origin - segment.get_EndPoint());
		int dir3 = segment.Vector.direction(segment.Origin - Origin);
		int dir4 = segment.Vector.direction(segment.Origin - get_EndPoint());

		//std::cout << "P1 X:" << segment.Origin.X << " Y: " << segment.Origin.Y << "\n";
		//std::cout << "P2 X:" << segment.get_EndPoint().X << " Y: " << segment.get_EndPoint().Y << "\n";
		//std::cout << "Dir1: " << dir1 << " Dir2: " << dir2 << "\n";

		//std::cout << "P3 X:" << Origin.X << " Y: " << Origin.Y << "\n";
		//std::cout << "P4 X:" << get_EndPoint().X << " Y: " << get_EndPoint().Y << "\n";
		//std::cout << "Dir3: " << dir3 << " Dir4: " << dir4 << "\n";
		//system("pause");

		// Does Lines Cross?
		if (((dir1 < 0 && dir2 > 0) || (dir1 > 0 && dir2 < 0)) &&
			((dir3 < 0 && dir4 > 0) || (dir3 > 0 && dir4 < 0)))
		{
			result.DoesCollide = true;
		}
		else
		{
			//std::cout << "Dir1: " << dir1 << " Dir2: " << dir2 << "\n";
			//std::cout << "Dir3: " << dir3 << " Dir4: " << dir4 << "\n";
		}

		// Point on Segment?
		if (dir1 == 0) result.DoesCollide = onSegment(segment.Origin);
		else if (dir2 == 0) result.DoesCollide = onSegment(segment.get_EndPoint());
		else if (dir3 == 0) result.DoesCollide = segment.onSegment(Origin);
		else if (dir4 == 0) result.DoesCollide = segment.onSegment(get_EndPoint());

		// Calculate Collisionpoint
		if (result.DoesCollide == true)
		{
			result.CollisionPoint.X = ((segment.getOffsetY() - this->getOffsetY()) / (this->getSlope() - segment.getSlope()));
			result.CollisionPoint.Y = getSlope() * result.CollisionPoint.X + getOffsetY();
		}

		//std::cout << "Location X: " << result.CollisionPoint.X << " Y: " << result.CollisionPoint.Y << "\n";
	}
    return result;
}