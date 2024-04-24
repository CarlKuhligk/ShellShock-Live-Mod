#pragma once

// Defines
# define M_PI           3.14159265358979323846f  /* pi */


class AimerOBJ : public MemorySSL
{
	// Variabels
private:
	BYTE rawDataBuffer[10 * 4]; // 0x08 to 0x30

public:
	BYTE* IsActivePointer = nullptr;
	bool IsActive = false;
	int Angle = 0;
	int Velocity = 0; // 0 to +100
	bool Enable = false;
	bool NewTurn = false;
	Vector2 VelocityVector;

	// Methodes
	AimerOBJ();

	bool readData();

};