#include "ChartCreator.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>

//helper functions
int generateChordSize(std::vector<int>& distributions, int keyCount);
std::pair<int, int> getAdjacentPair(int a, int b, int exclude);
std::pair<int, int> getNonAdjacentPair(int a, int b, int exclude);
bool contains(std::pair<int, int> p, int x);
int distance(int a, int b);

std::string convertToHitObject(int timeStamp, int columnNumber, int keyCount) {
	// x ,  y , time, type , objParams , hitsounds
	//192, 192, 3664, 1    , 0         , 0:0:0:0:

	int x;
	if (keyCount == 4) {
		x = get4kXValue(columnNumber);
	}
	else if (keyCount == 6) {
		x = get6kXValue(columnNumber);
	}
	else {
		x = get7kXValue(columnNumber);
	}

	std::string hitObject = "";
	hitObject += std::to_string(x);
	hitObject += ",192,";
	hitObject += std::to_string(timeStamp);
	hitObject += ",1,0,0:0:0:0:";
	return hitObject;
}

int get4kXValue(int columnNumber) {
	int x;
	switch (columnNumber) {
	case 0 : x = 64; break;
	case 1 : x = 192; break;
	case 2 : x = 320; break;
	case 3 : x = 448; break;
	default: x = 64; break;
	}
	return x;
}
int get6kXValue(int columnNumber) {
	int x;
	switch (columnNumber) {
	case 0: x = 42; break;
	case 1: x = 128; break;
	case 2: x = 213; break;
	case 3: x = 298; break;
	case 4: x = 384; break;
	case 5: x = 469; break;
	default: x = 42; break;
	}
	return x;
}
int get7kXValue(int columnNumber) {
	int x;
	switch (columnNumber) {
	case 0 : x = 36; break;
	case 1 : x = 109; break;
	case 2 : x = 182; break;
	case 3 : x = 256; break;
	case 4 : x = 329; break;
	case 5 : x = 402; break;
	case 6 : x = 475; break;
	default: x = 36; break;
	}
	return x;
}


std::vector<std::string> createChartsHitObjects(std::set<int> timeStamps, int keyCount, std::vector<int> distributions) {
	std::srand(std::time(0));
	std::vector<std::string> hitObjects;
	//for each timestamp
	for (int time : timeStamps) {
		int noteCount = generateChordSize(distributions, keyCount);
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

int generateChordSize(std::vector<int>& distributions, int keyCount) {
	int roll = std::rand() % 100 + 1;
	for (int i = 0; i < distributions.size(); i++) {
		if (roll <= distributions[i]) return i + 1;
		roll -= distributions[i];
	}
	return keyCount;
}

std::vector<std::string> createJumpStreamChart(std::set<int> timeStamps, int keyCount, int splitChordPercentage) {
	std::vector<std::string> hitObjects;
	if (keyCount != 4) {
		std::cout << keyCount << 'k' << " not supported with jumpstream mode" << std::endl;
		return hitObjects;
	}

	std::srand(std::time(0));
	std::set<int> previous{0};
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

std::pair<int,int> getAdjacentPair(int a, int b, int exclude = -1) {
	int size = b - a + 1;
	std::pair<int, int> p(std::rand() % size, std::rand() % size);
	while (contains(p, exclude) or distance(p.first, p.second) != 1) {
		p = { std::rand() % size, std::rand() % size };
	}
	return p;
}

std::pair<int, int> getNonAdjacentPair(int a, int b, int exclude = -1) {
	int size = b - a + 1;
	std::pair<int, int> p(std::rand() % size, std::rand() % size);
	while (contains(p, exclude) or distance(p.first, p.second) <= 1) {
		p = { std::rand() % size, std::rand() % size };
	}
	return p;
}

bool contains(std::pair<int,int> p, int x) {
	return p.first == x or p.second == x;
}

int distance(int a, int b) {
	return std::abs(a - b);
}

//saving this for a rainy day
//WORKS WELL FOR LONG JACKS ?
/*while (columns.find(column) == columns.end()) {
	column = std::rand() % 4;
	columns.insert(column);
}*/