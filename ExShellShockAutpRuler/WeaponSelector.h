#pragma once

class WeaponSelectorOBJ : public MemorySSL
{
public:

	std::string Name;
	int Stage = 0;
	int WeaponID;

	// Methodes
	WeaponSelectorOBJ();

	void readData();


};