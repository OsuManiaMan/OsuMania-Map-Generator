#include "LayeredStairsOptions.h"

void LayeredStairsOptions::presentOptions() {
	diffname = askForDiffname(diffname);

	print("Would you like to specify the number of stairs, default is 2 stairs?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter either 1, 2, 3, or 4.");
		printLine("Larger number = more dense");
		print("> ");
		stairCount = getInt(1,4);
	}
}

std::string LayeredStairsOptions::getDiffname() {
	return diffname;
}

int LayeredStairsOptions::getStairCount() {
	return stairCount;
}