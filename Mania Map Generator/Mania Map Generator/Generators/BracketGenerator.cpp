#include "BracketGenerator.h"
#include <iostream>
#include <queue>
#include <utility>
#define TRIALS 75

std::set<int> getRandomStart();

BracketGenerator::BracketGenerator(int missingPercentage)
	: missingPercentage(missingPercentage) {

}

//inherited
std::vector<std::string> BracketGenerator::generateHitObjects(std::set<int> timeStamps, int keyCount) {
	std::vector<std::string> hitObjects;
	std::srand(std::time(0));

	switch (keyCount) {
	case 4: return generateHitObjects4k(timeStamps);
	//case 6: return generateHitObjects6k(timeStamps);
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
	std::vector<std::string> hitObjects;
	std::vector<std::set<int>> notes = generateNotes7k(timeStamps.size());
	int i = 0;
	for (int time : timeStamps) {
		std::set<int> columns = notes[i++];
		for (int column : columns) {
			hitObjects.push_back(convertToHitObject(time, column, 7));
		}
	}
	return hitObjects;
}

std::vector<std::set<int>> BracketGenerator::generateNotes7k(int timeStampsCount) {
	//very shitty algorithm but it gets the job done
	std::cout << "Determining best pattern. This may take a minute." << std::endl;
	typedef std::pair<int, std::vector<std::set<int>>> pivs;
	std::set<int> previous;
	std::set<int> columns;
	std::vector<std::set<int>> beat;
	std::priority_queue<pivs, std::vector<pivs>, std::greater<pivs>> beats;

	//previous = getRandomStart();
	//beat.push_back(previous);

	srand(time(0));
	for (int trials = 0; trials < TRIALS; trials++) {
		//test
		previous = getRandomStart();
		beat.push_back(previous);

		int sway = 0;
		bool startIsOdd = *previous.begin() % 2;
		bool consistent = false;
		for (int k = 0; k < timeStampsCount / 4 + 10; k++) {

			if (previous.size() == 1) {
				bool isOdd = *previous.begin() % 2;
				int newCol = rand() % 7;
				while ((newCol % 2 != isOdd) or distance(newCol, *previous.begin()) < 2) {
					newCol = rand() % 7;
				}
				previous.insert(newCol);
			}
			else if (previous.size() == 0) {
				int newCol = rand() % 5;
				while (newCol % 2 != startIsOdd) {
					newCol = rand() % 5;
				}
				previous.insert(newCol);
				previous.insert(newCol + 2);
			}

			consistent = randomWithSway(consistent, sway);
			enum Direction { LEFT, RIGHT, NONE, OUT, IN };
			Direction direction = NONE;
			Direction flop = NONE;
			std::set<int> original = previous;
			/*for (int i : previous) {
				cout << i << ' ';
			}cout << "previous" << endl;*/
			for (int i = 0; i < 4; i++) {
				columns.clear();
				if (consistent) {
					if (direction == NONE or i == 2) {
						direction = (Direction)(rand() % 2);
					}
					for (int pCol : previous) {
						if (direction == LEFT) {
							if (pCol - 1 >= 0) {
								columns.insert(pCol - 1);
							}
						}
						else {
							if (pCol + 1 < 7) {
								columns.insert(pCol + 1);
							}
						}
					}
					if (columns.size() == 1) {
						int col = *columns.begin();
						if (col > 3)
							columns.insert(3 - distance(col, 3));
						else if (col < 3)
							columns.insert(3 + distance(col, 3));
						else
							columns.insert((rand() % 2) ? 1 : 5);
					}
				}
				else { // no direction typical brackets
					if (i % 2 == 1) {
						columns = original;
					}
					else {
						if (flop == NONE) {
							flop = (Direction)(rand() % 2 + 3);
						}
						if (flop == IN and (previous.size() != 1 or *previous.begin() != 3)) {
							for (int pCol : previous) {
								if (pCol < 3) {
									columns.insert(pCol + 1);
								}
								else if (pCol > 3) {
									columns.insert(pCol - 1);
								}
							}
						}
						else {
							for (int pCol : previous) {
								if (pCol - 1 >= 0) columns.insert(pCol - 1);
								if (pCol + 1 < 7) columns.insert(pCol + 1);
							}
						}
					}

				}
				//more thumb
				if (columns.find(2) == columns.end() and columns.find(4) == columns.end() and previous.find(3) == previous.end()) {
					if (rand() % 100 < 10) {
						columns.insert(3);
					}
				}
				beat.push_back(columns);
				previous = columns;
			}
		}
		beats.push(make_pair(calculateHandUsage(beat), beat));
		
		//test
		beat.clear();
		previous = getRandomStart();
		beat.push_back(previous);
	}
	return beats.top().second;
}


