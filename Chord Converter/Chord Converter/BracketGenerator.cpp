#include "BracketGenerator.h"
#include <iostream>

BracketGenerator::BracketGenerator(int missingPercentage)
	: missingPercentage(missingPercentage) {

}

//inherited
std::vector<std::string> BracketGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::vector<std::string> hitObjects;
	std::srand(std::time(0));

	switch (keyCount) {
	case 4: return generateHitObjects4k(timeStamps);
	case 6: return generateHitObjects6k(timeStamps);
	case 7: return generateHitObjects7k(timeStamps);
	default:
		std::cout << keyCount << "k doesn't support bracket pattern" << std::endl;
		return hitObjects;
	}

	return hitObjects;
}

std::vector<std::string> BracketGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount, int missingPercentage) {
	this->missingPercentage = missingPercentage;
	return generateHitObjects(timeStamps, keyCount);
}

std::vector<std::string> BracketGenerator::generateHitObjects4k(std::set<int> timeStamps) {
	std::vector<std::string> hitObjects;
	int  left[] = {0, 2};
	int right[] = {1, 3};
	bool flag = true;
	for (int time : timeStamps) {
		std::set<int> columns;
		int missing = -1; //-1 because its an invalid index for the above arrays
		//pick missing note if roll is within specified limit
		if (std::rand() % 100 < missingPercentage) {
			missing = std::rand() % 2;
		}
		//place notes but skip if note is marked as missing
		int* side = flag ? left : right;
		for (int i = 0; i < 2; i++) {
			if (i != missing) {
				columns.insert(side[i]);
			}
		}
		//compile
		for (int column : columns) {
			hitObjects.push_back(convertToHitObject(time, column, 4));
		}
		flag = !flag; //flip the flag bit
	}
	return hitObjects;
}

std::vector<std::string> BracketGenerator::generateHitObjects6k(std::set<int> timeStamps) {

}

std::vector<std::string> BracketGenerator::generateHitObjects7k(std::set<int> timeStamps) {

}

