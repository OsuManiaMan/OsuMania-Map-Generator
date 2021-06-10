#pragma once
#include "Options.h"
#include <string>

class JumpstreamOptions : public Options
{
private:
	std::string diffname = "JUMPSTREAM";
	int splitChordPercentage = 33;

public:
	void presentOptions() override;
	std::string getDiffname() override;
	int getSplitChordPercentage();
};

