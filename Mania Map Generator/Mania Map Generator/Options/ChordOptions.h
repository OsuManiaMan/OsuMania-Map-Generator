#pragma once
#include "Options.h"
#include <string>
#include <vector>

class ChordOptions : public Options
{
private:
	int keyCount = 4;
	std::string diffname = "CHORDS";
	std::vector<int> distributions;

public:
	ChordOptions(int keyCount);
	void presentOptions() override;
	void setKeyCount(int keyCount);
	std::string getDiffname() override;
	std::vector<int> getDistributions();
};

