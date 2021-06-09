#pragma once
#include "Options.h"

class LayeredStairsOptions : public Options
{
private:
	std::string diffname = "LAYERED STAIRS";
	int stairCount = 2;

public:
	void presentOptions() override;
	std::string getDiffname() override;
	int getStairCount();
};

