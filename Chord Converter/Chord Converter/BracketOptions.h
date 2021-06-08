#pragma once
#include "Options.h"
#include <string>

class BracketOptions : public Options
{
private:
	std::string diffname = "BRACKETS";
	int missingPercentage = 30;

public:
	void presentOptions() override;
	std::string getDiffname() override;
	int getMissingPercentage();
};

