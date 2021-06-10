#pragma once
#include "Options.h"
#include <string>

class StreamOptions : public Options
{
private:
	std::string diffname = "SINGLE STREAM";

public:
	void presentOptions() override;
	std::string getDiffname() override;
};

