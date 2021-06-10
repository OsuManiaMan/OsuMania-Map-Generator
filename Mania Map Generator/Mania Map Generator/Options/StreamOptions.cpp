#include "StreamOptions.h"

StreamOptions::StreamOptions(int trillPercentage) : trillPercentage(trillPercentage) {}

void StreamOptions::presentOptions() {
	diffname = askForDiffname(diffname);

	print("Would you like to mix in trills?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		trillPercentage = -2;
	}

	if (trillPercentage == -2) {
		print("Would you like to specify percentage of trills, default is 50%?(y/n): ");
		answer = getString();
		if (answer != "n") {
			printLine("Enter a number from 0-100");
			trillPercentage = getInt(0, 100);
		}
	}
}

std::string StreamOptions::getDiffname() {
	return diffname;
}

int StreamOptions::getTrillPercentage() {
	return trillPercentage;
}