#include "Generator.h"

int get4kXValue(int columnNumber) {
	int x;
	switch (columnNumber) {
	case 0: x = 64; break;
	case 1: x = 192; break;
	case 2: x = 320; break;
	case 3: x = 448; break;
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
	case 0: x = 36; break;
	case 1: x = 109; break;
	case 2: x = 182; break;
	case 3: x = 256; break;
	case 4: x = 329; break;
	case 5: x = 402; break;
	case 6: x = 475; break;
	default: x = 36; break;
	}
	return x;
}

std::string Generator::convertToHitObject(int timeStamp, int columnNumber, int keyCount) {
	// x ,  y , time, type , objParams , hitsounds
	//192, 192, 3664, 1    , 0         , 0:0:0:0:

	//determine x value for note
	int x;
	switch (keyCount) {
		case 4 : x = get4kXValue(columnNumber); break;
		case 6 : x = get6kXValue(columnNumber); break;
		default: x = get7kXValue(columnNumber); break;
	}
	
	//compile info into osu formatted hit object
	std::string hitObject = "";
	hitObject += std::to_string(x);
	hitObject += ",192,";
	hitObject += std::to_string(timeStamp);
	hitObject += ",1,0,0:0:0:0:";
	return hitObject;
}

std::pair<int, int> Generator::getAdjacentPair(int a, int b, int exclude) {
	int size = b - a + 1;
	std::pair<int, int> p(std::rand() % size, std::rand() % size);
	while (contains(p, exclude) or distance(p.first, p.second) != 1) {
		p = { std::rand() % size, std::rand() % size };
	}
	return p;
}

std::pair<int, int> Generator::getNonAdjacentPair(int a, int b, int exclude) {
	int size = b - a + 1;
	std::pair<int, int> p(std::rand() % size, std::rand() % size);
	while (contains(p, exclude) or distance(p.first, p.second) <= 1) {
		p = { std::rand() % size, std::rand() % size };
	}
	return p;
}

bool Generator::contains(std::pair<int, int> p, int x) {
	return p.first == x or p.second == x;
}

int Generator::distance(int a, int b) {
	return std::abs(a - b);
}

bool Generator::randomWithSway(bool last, int& sway) {
	int percentage = 50;
	for (int i = abs(sway); i > 0; i--) {
		percentage /= 2;
	}
	if (sway < 0) {
		percentage = 100 - percentage;
	}

	bool outcome = rand() % 100 < percentage;

	//adjust sway
	if (outcome != last)
		sway = 0;
	else if (outcome)
		sway++;
	else
		sway--;

	return outcome;
}

int Generator::calculateHandUsage(std::vector<std::set<int>> notes) {
	int balance = 0;
	for (std::set<int> timestamp : notes) {
		for (int col : timestamp) {
			balance += (col < 3) ? -1 : 1;
		}
	}
	return abs(balance);
}

std::set<int> Generator::getRandomStart() {
	std::set<int> columns;
	int noteCount = rand() % 4 + 1;
	if (noteCount == 4) {
		return std::set<int>{0, 2, 4, 6};
	}
	else if (noteCount == 3) {
		int start = rand() % 2;
		for (int i = start; i < 7; i += 2) {
			columns.insert(i);
		}
		return columns;
	}
	else if (noteCount == 2) {
		int start = rand() % 5;
		columns.insert(start);
		columns.insert(start + 2);
		return columns;
	}
	else {
		return std::set<int>{rand() % 7};
	}
}