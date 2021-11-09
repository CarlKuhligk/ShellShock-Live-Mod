#pragma once

struct CollisionLayer
{
	int Terrain = 0;
	int Projectile = 1;
	int Reflector = 2;
	int Protal = 3;
	int Blackhole = 4;
};

extern CollisionLayer Layer;

// Settigs of Collisions between Layers
extern std::vector<std::vector<bool>> CollideMatrix;