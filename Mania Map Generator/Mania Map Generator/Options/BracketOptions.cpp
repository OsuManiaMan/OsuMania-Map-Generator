#include "BracketOptions.h"

BracketOptions::BracketOptions(int keyCount) : keyCount(keyCount) {}

void BracketOptions::presentOptions() {
	diffname = askForDiffname(diffname);

	if (keyCount == 4) {
		printLine("Missing notes:");
		printLine("A missing note is exactly what it sounds like. Here's an example:");
		printLine("# # ");
		printLine(" #  ");
		printLine("# # ");
		printLine(" # #");
		printLine("# # ");
		print("Would you like to specify missing note chance, default is 30%?(y/n): ");
		std::string answer = getString();
		if (answer != "n") {
			printLine("Enter a whole number between 0-100.");
			printLine("It is the percentage that a note will be missing.");
			printLine("Low = more full bracket pattern and high = more random but less dense");
			print("> ");
			missingPercentage = getInt();
		}
	}
	else {
		print("Would you like to choose a generator?(y/n): ");
		std::string answer = getString();
		if (answer != "n") {
			printLine("Choose a generator:");
			printLine("[1] Less dense");
			printLine("[2] Better but more dense (I recommend this one if your not sure, this is the default generator)");
			print("> ");
			generator = getInt(1, 2);
		}
	}
}

std::string BracketOptions::getDiffname() {
	return diffname;
}

int BracketOptions::getMissingPercentage() {
	return missingPercentage;
}

int BracketOptions::getGenerator() {
	return generator;
}