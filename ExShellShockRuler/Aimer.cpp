#include "IncludeHead.h"

//__________Aimer__________
// Methodes
AimerOBJ::AimerOBJ()
{

}

bool AimerOBJ::readData()
{
	readBytes(ObjectAddress + 0x08, rawDataBuffer, sizeof(rawDataBuffer));

	// Doublecheck Activestate
	memcpy(&IsActivePointer, &rawDataBuffer[0x08 - 0x08], 4);

	// Aimeractive
	if (IsActivePointer != nullptr)
	{
		IsActive = true;
	}
	else
	{
		IsActive = false;
	}

	if (IsActive == true)
	{
		// Copy RAW Data
		bool changeDetected = false;
		int tempAngle, tempEnable;
		int tempVelocity;
		memcpy(&tempAngle, &rawDataBuffer[0x1C - 0x08], 4);
		memcpy(&tempVelocity, &rawDataBuffer[0x20 - 0x08], 4); // Velocity 0-100 to 0-1
		memcpy(&tempEnable, &rawDataBuffer[0x2C - 0x08], 4);

		// Translate Angle
		tempAngle = 90 - tempAngle;
		if (tempAngle < 0) tempAngle += 360;

		// Check for changes
		if (tempAngle != Angle) changeDetected = true;
		if (tempVelocity != Velocity) changeDetected = true;
		if (tempEnable != Enable) changeDetected = true;

		// Set new Data if a deviation apprears
		if (changeDetected == true)
		{
			// Detect new Turn
			if (Enable == false && tempEnable == true)
				NewTurn = true;

			// Set new Data
			Angle = tempAngle;
			Velocity = tempVelocity;
			Enable = tempEnable;

			// Calculate vX & Vy
			VelocityVector.X = cos(((float)Angle * M_PI) / 180) * Velocity;
			VelocityVector.Y = sin(((float)Angle * M_PI) / 180) * Velocity;
		}
		return changeDetected;
	}
	return false;
}
