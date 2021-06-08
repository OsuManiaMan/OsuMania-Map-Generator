#include "MainOptions.h"

#include <set>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <cmath>
#include "BracketGenerator.h"
using namespace std;

bool randomWithSway(bool last, int& sway) {
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

	cout << "percentage: " << percentage << "outcome: " << outcome << endl;
	return outcome;
}

int main() {
	BracketGenerator g;
	set<int> previous;
	set<int> columns;
	vector<set<int>> beat;
	int a, b, c, d;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	if (a > -1) {
		previous.insert(a);
	}
	if (b > -1) {
		previous.insert(b);
	}
	if (c > -1) {
		previous.insert(c);
	}
	if (d > -1) {
		previous.insert(d);
	}
	beat.push_back(previous);

	srand(time(0));
	int sway = 0;
	bool startIsOdd = *previous.begin() % 2;
	bool consistent = false;
	for (int k = 0; k < 25; k++) {

		if (previous.size() == 1) {
			bool isOdd = *previous.begin() % 2;
			int newCol = rand() % 7;
			while (newCol % 2 and !isOdd or g.distance(newCol, *previous.begin()) < 2) {
				newCol = rand() % 7;
			}
			previous.insert(newCol);
		}
		else if (previous.size() == 0) {
			int newCol = rand() % 5;
			while (newCol % 2 and !startIsOdd) {
				newCol = rand() % 5;
			}
			previous.insert(newCol);
			previous.insert(newCol + 2);
		}

		consistent = randomWithSway(consistent, sway);
		enum Direction { LEFT, RIGHT, NONE, OUT, IN };
		Direction direction = NONE;
		Direction flop = NONE;
		set<int> original = previous;
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
						columns.insert(3 - g.distance(col, 3));
					else if (col < 3)
						columns.insert(3 + g.distance(col, 3));
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
			beat.push_back(columns);
			previous = columns;
		}
	}

	for (auto row : beat) {
		for (int i = 0; i < 7; i++) {
			if (row.find(i) != row.end()) {
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

	MainOptions mainMenu;
	mainMenu.presentOptions();
	return 0;
}