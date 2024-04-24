#pragma once



class PlayerOBJ : public MemorySSL
{
	// Variabels
private:
	BYTE rawDataBuffer[22 * 4];
	//const float gunOffset = 0.1f;

public:

	// Playerdata
	bool MySelf = false;
	std::string SteamId = "";
	std::string Name = "";
	Point2 TankPosition;
	Point2 GunPosition;
	Vector2 VelocityVector;

	int Level = 0;
	int Team = 0;
	int Fuel = 0;
	bool IsConnected = false;
	int Health = 0;
	int Amor = 0;
	int Hitpoints = 0;
	int Angle = 0;
	int Velocity = 0;
	bool LockedIn = false;
	bool IsEnemy = false;
	int DeadData = 0;

	// Methodes
	PlayerOBJ(BYTE* baseAddress);

	// Reads the entire PlayerDataStructure (from 0x38 to 0x8C)
	bool readData();


	~PlayerOBJ();

};