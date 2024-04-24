#include "IncludeHead.h"

CollisionLayer Layer;

// Settigs of Collisions between Layers
std::vector<std::vector<bool>> CollideMatrix =
{// Collide with     L0 L1 L2 L3 L4 L5
	/* Layer0 */	{0, 1, 0, 0, 0, 0, 0},	// Terrain
	/* Layer1 */	{1, 0, 1, 1, 1, 0, 0},	// Projectile
	/* Layer2 */	{0, 1, 0, 0, 0, 0, 0},	// Reflector
	/* Layer3 */	{0, 1, 0, 0, 0, 0, 0},	// Protal
	/* Layer4 */	{0, 1, 0, 0, 0, 0, 0},	// Blackhole
	/* Layer5 */	{0, 0, 0, 0, 0, 0, 0},
	/* Layer6 */	{0, 0, 0, 0, 0, 0, 0}
};