#include "LayeredStairsGenerator.h"
#include "BracketGenerator.h"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <iostream>
#include <utility>
#define TRIALS 75

LayeredStairsGenerator::LayeredStairsGenerator(int stairCount) : stairCount(stairCount) {}

//inherited
std::vector<std::string> LayeredStairsGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::srand(std::time(0));
	std::vector<std::string> hitObjects;
	std::vector<std::set<int>> notes = generateNotes(timeStamps.size(), keyCount);

	int i = 0;
	for (int time : timeStamps) {
		std::set<int> columns = notes[i++];
		for (int column : columns) {
			hitObjects.push_back(convertToHitObject(time, column, keyCount));
		}
	}
	return hitObjects;
}

std::vector<std::set<int>> LayeredStairsGenerator::generateNotes(int timeStampCount, int keyCount) {
	std::cout << "Determining best pattern. This may take a minute." << std::endl;
	typedef std::pair<int, std::vector<std::set<int>>> pivs;
	std::set<int> previous;
	std::set<int> columns;
	std::vector<std::set<int>> beat;
	std::priority_queue<pivs, std::vector<pivs>, std::greater<pivs>> beats;

	std::srand(std::time(0));
	for (int trials = 0; trials < TRIALS; trials++) {
		if (stairCount == 2) {
			previous.insert(std::rand() % keyCount);
			previous.insert(std::rand() % keyCount);
			int dist = distance(*previous.begin(), *previous.rbegin());
			while (previous.size() != stairCount or dist < 2 or dist % 2 != 0) {
				previous.clear();
				previous.insert(std::rand() % keyCount);
				previous.insert(std::rand() % keyCount);
				dist = distance(*previous.begin(), *previous.rbegin());
			}
		}
		else {
			previous = getRandomStart();
			while (previous.size() != stairCount) {
				previous = getRandomStart();
			}
		}
		
		//beat.push_back(previous);
		enum Direction { LEFT, RIGHT, NONE };
		for (int startCol : previous) {
			int idx = 0;
			int prevCol = startCol;
			int sway = 0;
			Direction direction = NONE;
			bool left = false;
			for (int i = 0; i < timeStampCount / 8 + 10; i++) {
				left = randomWithSway(left, sway);
				direction = left ? LEFT : RIGHT;
				for (int j = 0; j < 8; j++) {
					if (std::rand() % 100 < 5) {
						left = randomWithSway(left, sway);
						direction = left ? LEFT : RIGHT;
					}
					int col;
					if (direction == LEFT) {
						col = prevCol - 1;
						if (col < 0) {
							col = 1;
							direction = RIGHT;
						}
					}
					else {
						col = prevCol + 1;
						if (col == keyCount) {
							col = keyCount - 2;
							direction = LEFT;
						}
					}
					if (beat.size() > idx) {
						beat[idx].insert(col);
					}
					else {
						beat.push_back(std::set<int>{col});
					}
					prevCol = col;
					idx++;
				}
			}
		}
		beats.push(make_pair(calculateHandUsage(beat), beat));
		beat.clear();
	}
	return beats.top().second;
}

//wrapper
std::vector<std::string> LayeredStairsGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount, int stairCount) {
	this->stairCount = stairCount;
	return generateHitObjects(timeStamps, keyCount);
}