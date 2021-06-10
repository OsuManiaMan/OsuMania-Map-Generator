#include "ChordOptions.h"

ChordOptions::ChordOptions(int keyCount) {
	this->keyCount = keyCount;
}

void ChordOptions::presentOptions() {
	diffname = askForDiffname(diffname);
	

	printLine("Would you like to specify chord distributions?(y/n): ");
	std::string answer = getString();

	//set up default distributions
	for (int i = 0; i < keyCount - 1; i++) {
		distributions.push_back(100 / keyCount);
	}
	distributions.push_back(100 - (100 / keyCount * (keyCount - 1)));

	if (answer != "n") {
		//if user chose to specify distributions, then prompt for chord size distributions
		printLine("Enter whole numbers between 0-100.");
		printLine("They are the percentages that a given chord size will appear.");
		printLine("Totals over 100% may result in errors.");
		int sum = 0;
		for (int i = 0; i < keyCount; i++) {
			print("Chords size ");
			print(i + 1);
			print(": ");
			distributions[i] = getInt(0, 100 - sum);
		}
	}
}

void ChordOptions::setKeyCount(int keyCount) {
	this->keyCount = keyCount;
}

std::string ChordOptions::getDiffname() {
	return diffname;
}

std::vector<int> ChordOptions::getDistributions() {
	return distributions;
}