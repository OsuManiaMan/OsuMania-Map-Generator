#include "Options.h"
#include <iostream>

bool isInt(std::string s);

//Console output
void Options::print(std::string text) {
	std::cout << text;
}

void Options::print(int n) {
	std::cout << n;
}

void Options::printLine(std::string text) {
	std::cout << text << std::endl;
}

void Options::printLine(int n) {
	std::cout << n << std::endl;
}

//User input functions
std::string Options::getString() {
	std::string buffer;
	std::getline(std::cin, buffer);
	if (buffer.empty()) return getString();
	return buffer;
}

int Options::getInt(int lowerBound, int upperBound) {
	std::string buffer;
	std::getline(std::cin, buffer);
	if (!isInt(buffer)) {
		printLine("Invalid number entered. Enter a new number.");
		return getInt();
	}
	int n = std::stoi(buffer);
	if (n < lowerBound or n > upperBound) {
		printLine("Number entered not in valid range. Enter a new number.");
		print("Number must be between ");
		print(lowerBound);
		print(" and ");
		printLine(upperBound);
		return getInt();
	}
	return n;
}

//helper
bool isInt(std::string s) {
	if (s.empty()) return false;
	for (char c : s) {
		if (!std::isdigit(c)) return false;
	}
	return true;
}

std::string Options::askForDiffname(std::string defaultName) {
	print("Want a custom diff name?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter a name for the difficulty:");
		return getString();
	}
	return defaultName;
}