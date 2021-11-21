#include "IncludeHead.h"
//__________Player__________


// Methodes
PlayerOBJ::PlayerOBJ(BYTE* baseAddress)
{
	// Player gets created

	// Set Address
	ObjectAddress = baseAddress;

	// read the entire PlayerDataStructure (from 0x38 to 0x8C)
	readData();

	if (IsConnected == true)
	{
		// Initialize String Values
		SteamId = readString(readPointer(ObjectAddress + 0x08, { 0x08 }));
		Name = readString(readPointer(ObjectAddress + 0x08, { 0x0C }));
	}
}

PlayerOBJ::~PlayerOBJ()
{
	// Player gets deleted
}

// Reads the entire PlayerDataStructure (from 0x30 to 0x8C)
bool PlayerOBJ::readData()
{
	// PlayerData
	readBytes(ObjectAddress + 0x38, rawDataBuffer, sizeof(rawDataBuffer));

	//Dead memory
	BYTE tempBuffer[4];
	readBytes(readPointer(ObjectAddress + 0x28, {}) + 0x08, tempBuffer, sizeof(tempBuffer));
	memcpy(&DeadData, tempBuffer, 4);

	// Check if the Player is connected
	memcpy(&IsConnected, &rawDataBuffer[0x50 - 0x38], 4);

	// Temporary Data for Process Data
	bool changeDetected = false;
	int tempAngle, tempVelocity;
	float tempPositionX;

	if (IsConnected == true)
	{
		// Process Data
		// Copy RAW Data
		memcpy(&Level, &rawDataBuffer[0], 4);
		memcpy(&Team, &rawDataBuffer[0x3C - 0x38], 4);
		memcpy(&tempPositionX, &rawDataBuffer[0x44 - 0x38], 4);	// 0-1000 
		memcpy(&Fuel, &rawDataBuffer[0x48 - 0x38], 4);
		memcpy(&Health, &rawDataBuffer[0x54 - 0x38], 4);
		memcpy(&Amor, &rawDataBuffer[0x5C - 0x38], 4);
		memcpy(&tempAngle, &rawDataBuffer[0x84 - 0x38], 4);
		memcpy(&tempVelocity, &rawDataBuffer[0x88 - 0x38], 4);
		memcpy(&LockedIn, &rawDataBuffer[0x8C - 0x38], 4);
		Hitpoints = Health + Amor;

		// Translate Angle
		tempAngle = 90 - tempAngle;
		if (tempAngle < 0) tempAngle += 360;

		// Check for changes
		if (tempAngle != Angle) changeDetected = true;
		if (tempVelocity != Velocity) changeDetected = true;
		if (tempPositionX != TankPosition.X) changeDetected = true;

		// Set new Data
		Angle = tempAngle;
		Velocity = tempVelocity;
		TankPosition.X = tempPositionX;

		// Calculate vX & Vy
		VelocityVector.X = cos(((float)Angle * M_PI) / 180) * Velocity;
		VelocityVector.Y = sin(((float)Angle * M_PI) / 180) * Velocity;

	}

	return changeDetected;
}


