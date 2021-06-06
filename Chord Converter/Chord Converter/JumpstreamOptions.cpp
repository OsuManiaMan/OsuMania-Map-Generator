#include "JumpstreamOptions.h"

void JumpstreamOptions::presentOptions() {
	print("Want a custom diff name?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter a name for the difficulty:");
		diffname = getString();
	}

	printLine("Split chords:");
	printLine("A split chord is a chord with non-adjacent notes, like this pattern for example");
	printLine("#  #");
	printLine(" #  ");
	printLine("# # ");
	printLine("   #");
	printLine("# # ");
	print("Would you like to specify split chord chance, default is 33%?(y/n): ");
	answer = getString();
	if (answer != "n") {
		printLine("Enter a whole number between 0-100.");
		printLine("It is the percentage that a split chord will appear.");
		printLine("Low = more jack based and high = more messy");
		print("> ");
		splitChordPercentage = getInt();
	}
}

std::string JumpstreamOptions::getDiffname() {
	return diffname;
}

int JumpstreamOptions::getSplitChordPercentage() {
	return splitChordPercentage;
}