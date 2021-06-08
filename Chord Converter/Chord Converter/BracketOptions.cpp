#include "BracketOptions.h"

void BracketOptions::presentOptions() {
	print("Want a custom diff name?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter a name for the difficulty:");
		diffname = getString();
	}

	printLine("Missing notes:");
	printLine("A missing note is exactly what it sounds like. Here's an example:");
	printLine("# # ");
	printLine(" #  ");
	printLine("# # ");
	printLine(" # #");
	printLine("# # ");
	print("Would you like to specify missing note chance, default is 30%?(y/n): ");
	answer = getString();
	if (answer != "n") {
		printLine("Enter a whole number between 0-100.");
		printLine("It is the percentage that a note will be missing.");
		printLine("Low = more full bracket pattern and high = more random but less dense");
		print("> ");
		missingPercentage = getInt();
	}
}

std::string BracketOptions::getDiffname() {
	return diffname;
}

int BracketOptions::getMissingPercentage() {
	return missingPercentage;
}