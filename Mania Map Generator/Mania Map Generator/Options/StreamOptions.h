#pragma once
#include "Options.h"
#include <string>

class StreamOptions : public Options
{
private:
	std::string diffname = "SINGLE STREAM";
	int trillPercentage = 0;

public:
	StreamOptions(int trillPercentage = 0);
	void presentOptions() override;
	std::string getDiffname() override;
	int getTrillPercentage();
};

