#pragma once
class PolyLineCollider2D;

class TerrainOBJ : public MemorySSL
{
	// Variabels
public:
	BYTE rawDataBuffer[201 * 8] = {};

public:
	const int Size = 201;
	Point2 Points[201] = {};
	PolyLineCollider2D PolyLineCollider = PolyLineCollider2D(Layer.Terrain);

	// Methodes
	TerrainOBJ();

	void readData();

};