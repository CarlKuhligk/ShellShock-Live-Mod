#pragma once

class LineCollider2D;


typedef struct ProjEventType
{
	int MaxHight = 0;
	int Collision = 1;
	int Time = 2;
	int Distance = 3;
	int Protal = 4;
	int Blackhole = 5;
};
extern ProjEventType ProjectileEventType;


typedef struct ProjectileEvent
{
	Point2 Location;
	float Time;
	int Type;
};


class Projectile
{
public:
	// Variabels
	Point2 Position;
	Vector2 Velocity;
	float WindEffect = 1;
	float GravityEffect = 1;
	float LifeTime = 0;
	float DeltaTime = 0;
	float EventTimer1 = 0;
	float EventTimer2 = 0;
	bool IsFlying = true;

	// Special
	float Size;
	int ID;
	int BounceCount;
	float BounceValue;

	// References
	static float* Gravity;
	static float* WindForce;
	static std::vector<Projectile>* Projectiles;
	static TerrainOBJ* Terrain;
	//static std::vector<LineCollider2D>* LineCollider;

			
	std::vector<Point2> TracePoints;
	std::vector<ProjectileEvent> Events;

	// Methodes
	Projectile(Point2 position, Vector2 velocity, int id);

	void setVelocity(Vector2 newVelocity);
	void updateVelocity(float deltaT);
	
	void Calculate(const float& deltaT);


	
	void Collided();
};
