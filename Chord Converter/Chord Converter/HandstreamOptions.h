#pragma once
#include "Options.h"
#include <string>

class HandstreamOptions : public Options
{
private:
	std::string diffname = "HANDSTREAM";
	int splitChordPercentage = 40;

public:
	void presentOptions() override;
	std::string getDiffname() override;
	int getSplitChordPercentage();
};
