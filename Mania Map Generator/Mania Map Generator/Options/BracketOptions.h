#pragma once
#include "../Options.h"
#include <string>

class BracketOptions : public Options
{
private:
	std::string diffname = "BRACKETS";
	int missingPercentage = 30;
	int keyCount = 4;
	int generator = 2;

public:
	BracketOptions(int keyCount);
	void presentOptions() override;
	std::string getDiffname() override;
	int getMissingPercentage();
	int getGenerator();
};

