#include "StreamGenerator.h"
#include <cstdlib>
#include <ctime>

StreamGenerator::StreamGenerator(int trillPercentage) : trillPercentage(trillPercentage) {}

std::vector<std::string> StreamGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::vector<std::string> hitObjects;
	std::srand(std::time(0));
	int reserve = 0;
	enum Pattern { ROLL, TRILL, NONE };
	enum Direction { LEFT, RIGHT };
	Pattern pattern = NONE;
	Direction direction = LEFT;
	int prevCol = std::rand() % keyCount;
	int currentCol, trillCol;
	int sway = 0;
	for (int time : timeStamps) {
		if (pattern == NONE or reserve == 0) {
			if (trillPercentage == -2) {
				pattern = (randomWithSway((int)pattern, sway)) ? ROLL : TRILL;
			}
			else {
				pattern = (std::rand() % 100 < trillPercentage) ? TRILL : ROLL;
			}
			
			reserve = std::rand() % keyCount + 1;
			if (pattern == ROLL) {
				direction = (std::rand() % 2) ? LEFT : RIGHT;
			}
			else {
				trillCol = std::rand() % keyCount;
				while (trillCol == prevCol) {
					trillCol = std::rand() % keyCount;
				}
				currentCol = prevCol;
			}
		}
		if (pattern == TRILL) {
			currentCol = trillCol;
			trillCol = prevCol;

			hitObjects.push_back(convertToHitObject(time, currentCol, keyCount));
			reserve--;
		}
		else {
			currentCol = (direction == LEFT) ? prevCol - 1 : prevCol + 1;
			if (currentCol == keyCount) {
				currentCol = 0;
			}
			else if (currentCol == -1) {
				currentCol = keyCount - 1;
			}
			hitObjects.push_back(convertToHitObject(time, currentCol, keyCount));
			reserve--;
		}
		prevCol = currentCol;
	}
	return hitObjects;
}