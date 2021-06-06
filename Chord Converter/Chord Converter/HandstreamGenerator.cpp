#include "HandstreamGenerator.h"
#include <iostream>

HandstreamGenerator::HandstreamGenerator(int splitChordPercentage)
	: splitChordPercentage(splitChordPercentage) {

}

//inherited
std::vector<std::string> HandstreamGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::vector<std::string> hitObjects;
	if (keyCount != 4) {
		std::cout << keyCount << 'k' << " not supported with handstream mode" << std::endl;
		return hitObjects;
	}

	int noteCounts[] = {3, 1, 2, 1};

	std::srand(std::time(0));
	std::set<int> previous;
	int noteCountIdx = 0;
	bool flag = true;
	for (int time : timeStamps) {
		//some stupid logic to make first note a single instead of a hand, should prob replace later
		if (flag) {
			int column = std::rand() % keyCount;
			hitObjects.push_back(convertToHitObject(time, column, keyCount));
			previous.insert(column);
			flag = false;
			continue;
		}
		

		std::set<int> columns;
		noteCountIdx += 1;
		noteCountIdx %= 4; // size of noteCounts
		if (noteCounts[noteCountIdx] == 2) {
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
		else if (noteCounts[noteCountIdx] == 3) {
			for (int i = 0; i < keyCount; i++) {
				if (previous.find(i) == previous.end()) {
					columns.insert(i);
				}
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
std::vector<std::string> HandstreamGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount, int splitChordPercentage) {
	this->splitChordPercentage = splitChordPercentage;
	return generateHitObjects(timeStamps, keyCount);
}

//setters
void HandstreamGenerator::setSplitChordPercentage(int splitChordPercentage) {
	this->splitChordPercentage = splitChordPercentage;
}