#include "ChordGenerator.h"
#include <cstdlib>
#include <ctime>

ChordGenerator::ChordGenerator(std::vector<int>* distributionsPtr) {
	if (distributionsPtr) {
		this->distributions = *distributionsPtr;
	}
}

std::vector<std::string> ChordGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::srand(std::time(0));
	std::vector<std::string> hitObjects;
	//for each timestamp
	for (int time : timeStamps) {
		int noteCount = generateChordSize(keyCount);
		std::set<int> columns;
		//generate notes at timestamp
		for (int i = 0; i < noteCount; i++) {
			int column = std::rand() % keyCount;
			//regenerate if column already in use
			while (columns.find(column) != columns.end()) {
				column = std::rand() % keyCount;
			}
			columns.insert(column);

		}
		//Convert time stamp and columns to hit objects
		for (int column : columns) {
			hitObjects.push_back(convertToHitObject(time, column, keyCount));
		}
		columns.clear();
	}

	return hitObjects;
}

std::vector<std::string> ChordGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount, std::vector<int> distributions) {
	this->distributions = distributions;
	generateHitObjects(timeStamps, keyCount);
}

//helpers
int ChordGenerator::generateChordSize(int keyCount) {
	int roll = std::rand() % 100 + 1;
	for (int i = 0; i < distributions.size(); i++) {
		if (roll <= distributions[i]) return i + 1;
		roll -= distributions[i];
	}
	return keyCount;
}

//setters
void ChordGenerator::setDistributions(std::vector<int> distributions) {
	this->distributions = distributions;
}




//saving this for a rainy day
//WORKS WELL FOR LONG JACKS ?
/*while (columns.find(column) == columns.end()) {
	column = std::rand() % 4;
	columns.insert(column);
}*/