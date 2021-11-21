#include "IncludeHead.h"


//__________Terrain__________
// Methodes
TerrainOBJ::TerrainOBJ()
{

}

void TerrainOBJ::readData()
{
	readBytes(ObjectAddress, rawDataBuffer, sizeof(rawDataBuffer));

	// Clear all Lines
	PolyLineCollider.clear();

	// Copy RAW Data
	for (int i = 0; i < Size; i++)
	{
		// Copy RawData in to Collider
		memcpy(&Points[i].X, &rawDataBuffer[i * 8], 4);
		memcpy(&Points[i].Y, &rawDataBuffer[i * 8 + 4], 4);

		// Translate Data to 0 - 1000 Coordinatesystem
		Points[i].X = Points[i].X * 100.0f + 500.0f;	// translate -5 +5 to  0-1000
		Points[i].Y = Points[i].Y * 100.0f + 500.0f;	// translate -5 +5 to  0-1000
		// add Point to Collider
		PolyLineCollider.addPoint(Points[i]);
	}
}
