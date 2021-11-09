#include "IncludeHead.h"

ProjEventType ProjectileEventType;

float* Projectile::Gravity = nullptr;
float* Projectile::WindForce = nullptr;
std::vector<Projectile>* Projectile::Projectiles = nullptr;
TerrainOBJ* Projectile::Terrain = nullptr;

Projectile::Projectile(Point2 position, Vector2 velocity, int id = 0)
{
	this->Position = position;
	this->Velocity = velocity;
	this->ID = id;
}

void Projectile::setVelocity(Vector2 newVelocity)
{
	// check for highest point Event
	if (newVelocity.Y < 0 && Velocity.Y > 0)
	{
		// Highespoint reacht
		
	}
}


void Projectile::updateVelocity(float deltaT)
{
	Velocity.X -= (*WindForce * WindEffect) * deltaT;
	Velocity.Y -= (*Gravity * GravityEffect) * deltaT;
}

void Projectile::Calculate(const float& time)
{
	while (IsFlying == true)
	{
		// Calculate traveled distance
		// X
		float dX = Velocity.X * time;
		// Y
		float dY = Velocity.Y * time;

		// Create LineCollider for collision check
		Segment travledDistance = Segment(Position, Vector2(dX, dY));
		LineCollider2D flightPath = LineCollider2D(travledDistance, Layer.Projectile);

		// Collision result
		CollisionResult collisionResult;

		// Collisioncheck with Terrain
		collisionResult = Terrain->PolyLineCollider.Collide(flightPath);
		if (collisionResult.DoesCollide == true)
		{
			// Collision with Terrain
			// Collide Event
			ProjectileEvent event;
			event.Location = collisionResult.CollisionPoint;
			event.Time = abs(collisionResult.CollisionPoint.X - Position.X) / Velocity.X;
			event.Type = ProjectileEventType.Collision;
			Events.push_back(event);

			// can it bounce?
			if (BounceCount > 0)
			{
				// Handle Bounce
			}
			else
			{
				// Projectile explodes
				Position = collisionResult.CollisionPoint;
				TracePoints.push_back(Position);
				IsFlying = false;
				return;
			}
			
		}

		// no collision
		// update Position
		Position.X += dX;
		Position.Y += dY;
		//
		TracePoints.push_back(Point2(Position.X, Position.Y));

		// set new Velocity
		updateVelocity(time);

		// update Time
		LifeTime += time;

		// Screenend
		if (Position.X > 1000 || Position.X < 0 || Position.Y < 0)
		{
			IsFlying = false;
		}

	}

}