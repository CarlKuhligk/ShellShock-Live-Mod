#include "IncludeHead.h"

//__________Wind__________
// Methodes
WindOBJ::WindOBJ()
{

}

void WindOBJ::readData()
{
	// Read Data
	Force = readValue<float>(ObjectAddress); // Force -1 to +1

	// Round
	if (Force > 0)
		Force += 0.005f;
	else
		Force -= 0.005f;

	Force *= 100.0f;
	Force = (int)Force;
	Force /= -100.0f;




	// Process Data
	if (Force > 0)
	{
		ForceRight = true;
		ForceLeft = false;
	}
	else if (Force < 0)
	{
		ForceRight = false;
		ForceLeft = true;
	}
	else
	{
		ForceRight = false;
		ForceLeft = false;
	}
}

