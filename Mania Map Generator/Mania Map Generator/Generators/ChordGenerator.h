#pragma once
#include "Generator.h"

class ChordGenerator : public Generator
{
private:
	std::vector<int> distributions;

public:
	ChordGenerator(std::vector<int>* distributionsPtr = nullptr);

	//inherited
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount) override;

	//wrapper
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount, std::vector<int> distributions);

	//helpers
	int generateChordSize(int keyCount);

	//setters
	void setDistributions(std::vector<int> distributions);
};

