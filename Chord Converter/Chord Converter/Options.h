#pragma once
#include <string>

class Options
{
public:
	virtual void presentOptions() = 0;
	virtual std::string getDiffname() = 0;

//Console output
	void print(std::string text);
	void print(int n);
	void printLine(std::string text);
	void printLine(int n);

//User input functions
	std::string getString();
	int getInt(int lowerBound = 0, int upperBound = 100);
};

