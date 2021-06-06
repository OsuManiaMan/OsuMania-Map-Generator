#pragma once
#include "Generator.h"
#include <vector>
#include <set>
#include <string>

class JumpstreamGenerator : public Generator
{
private:
	int splitChordPercentage;

public:
	JumpstreamGenerator(int splitChordPercentage = 33);

	//inherited
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount) override;

	//wrapper
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount, int splitChordPercentage);

	//setters
	void setSplitChordPercentage(int splitChordPercentage);
};

