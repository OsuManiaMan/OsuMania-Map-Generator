#include "JumpstreamGenerator.h"
#include <iostream>

JumpstreamGenerator::JumpstreamGenerator(int splitChordPercentage) 
	: splitChordPercentage(splitChordPercentage) {

}

//inherited
std::vector<std::string> JumpstreamGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::vector<std::string> hitObjects;
	if (keyCount != 4) {
		std::cout << keyCount << 'k' << " not supported with jumpstream mode" << std::endl;
		return hitObjects;
	}

	std::srand(std::time(0));
	std::set<int> previous{ 0 };
	int noteCount = 2;
	for (int time : timeStamps) {
		std::set<int> columns;
		noteCount = (noteCount > 1) ? 1 : 2;
		if (noteCount == 2) {
			if ((std::rand() % 100) < splitChordPercentage) {
				std::pair<int, int> p = getNonAdjacentPair(0, 3, *previous.begin());
				columns.insert(p.first);
				columns.insert(p.second);
			}
			else {
				std::pair<int, int> p = getAdjacentPair(0, 3, *previous.begin());
				columns.insert(p.first);
				columns.insert(p.second);
			}
		}
		else {
			int column = std::rand() % keyCount;
			while (previous.find(column) != previous.end()) {
				column = std::rand() % keyCount;
			}
			columns.insert(column);
		}

		for (int column : columns) {
			hitObjects.push_back(convertToHitObject(time, column, keyCount));
		}
		previous = columns;
	}
	return hitObjects;
}

//wrapper
std::vector<std::string> JumpstreamGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount, int splitChordPercentage) {
	this->splitChordPercentage = splitChordPercentage;
	return generateHitObjects(timeStamps, keyCount);
}

//setters
void JumpstreamGenerator::setSplitChordPercentage(int splitChordPercentage) {
	this->splitChordPercentage = splitChordPercentage;
}