#pragma once
#include "Generator.h"
#include <vector>
#include <string>
#include <set>

class StreamGenerator : public Generator 
{
private:
	int trillPercentage = 0;

public:
	StreamGenerator(int trillPercentage = 0);
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount) override;
};

