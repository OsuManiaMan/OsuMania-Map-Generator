#pragma once
#include "Options.h"
#include <string>

class MainOptions : Options
{
public:
	void presentOptions() override;
	std::string getDiffname() override;
};


