#pragma once

class WindOBJ : public MemorySSL
{
	// Variabels
public:
	float Force;
	bool ForceRight;
	bool ForceLeft;

	// Methodes
	WindOBJ();

	void readData();

};