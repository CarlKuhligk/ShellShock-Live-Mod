#include "IncludeHead.h"

//__________WeaponSelector__________
// Methodes
WeaponSelectorOBJ::WeaponSelectorOBJ()
{

}

void WeaponSelectorOBJ::readData()
{
	// Read Data
	Name = readString(readPointer(ObjectAddress + 0x0C, { 0x08 }));
	Stage = readValue<int>(ObjectAddress + 0x24);

	// Process Data
	// Build WeaponID
}