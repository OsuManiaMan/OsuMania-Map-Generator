#pragma once
#include "Generator.h"
#include <vector>
#include <string>
#include <set>

class StreamGenerator : public Generator 
{
public:
	std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount) override;
};

