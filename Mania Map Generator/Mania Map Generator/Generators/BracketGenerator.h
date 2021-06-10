#pragma once
#include "../Generator.h"
#include <vector>
#include <string>
#include <set>

class BracketGenerator : public Generator
{
private:
	int missingPercentage;
	std::vector<std::string> generateHitObjects4k(std::set<int> timeStamps);
	std::vector<std::string> generateHitObjects6k(std::set<int> timeStamps);
	std::vector<std::string> generateHitObjects7k(std::set<int> timeStamps);
	std::vector<std::set<int>> generateNotes7k(int timeStampCount);

public:
	BracketGenerator(int missingPercentage = 30);

	//inherited
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount);

	//wrapper
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount, int missingPercentage);
};
