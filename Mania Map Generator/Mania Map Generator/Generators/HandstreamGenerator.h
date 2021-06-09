#pragma once
#include "Generator.h"

class HandstreamGenerator : public Generator
{
private:
	int splitChordPercentage;

public:
	HandstreamGenerator(int splitChordPercentage = 40);

	//inherited
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount);

	//wrapper
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount, int splitChordPercentage);

	//setters
	void setSplitChordPercentage(int splitChordPercentage);
};

