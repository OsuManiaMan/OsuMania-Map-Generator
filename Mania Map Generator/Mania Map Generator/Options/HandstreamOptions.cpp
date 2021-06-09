#include "HandstreamOptions.h"

void HandstreamOptions::presentOptions() {
	diffname = askForDiffname(diffname);

	printLine("Split chords:");
	printLine("A split chord is a chord with non-adjacent notes, like this pattern for example");
	printLine("#  #");
	printLine(" #  ");
	printLine("# # ");
	printLine("   #");
	printLine("# # ");
	print("Would you like to specify split chord chance, default is 40%?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter a whole number between 0-100.");
		printLine("It is the percentage that a split chord will appear.");
		printLine("Low = more jack based and high = more messy");
		print("> ");
		splitChordPercentage = getInt();
	}
}

std::string HandstreamOptions::getDiffname() {
	return diffname;
}

int HandstreamOptions::getSplitChordPercentage() {
	return splitChordPercentage;
}