#pragma once
#include "Generator.h"
#include <set>
#include <vector>
#include <string>

class LayeredStairsGenerator : public Generator
{
private:
	int stairCount = 2;
	std::vector<std::set<int>> generateNotes(int timeStampCount, int keyCount);

public:
	LayeredStairsGenerator(int stairCount = 2);

	//inherited
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount);

	//wrapper
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount, int stairCount);
};

