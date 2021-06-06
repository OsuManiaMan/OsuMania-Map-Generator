#include "Options.h"
#include "MainOptions.h"
#include "ChordOptions.h"
#include "JumpstreamOptions.h"
#include "FileHandler.h"
#include "Generator.h"
#include "ChordGenerator.h"
#include "JumpstreamGenerator.h"
#include <cstdlib>
#include <climits>
#include <vector>
#include <set>

void MainOptions::presentOptions() {
	//have user select file
	std::string filename = getOsuFile();
	if (filename.empty()) {
		printLine("An error occured when selecting the file.");
		system("pause");
		exit(EXIT_FAILURE);
	}

	//get key count
	std::vector<std::string> filedata = getLines(filename);
	int keyCount = getKeyMode(filedata);

	//resolve pattern type
	int patternChosen = 1;
	if (keyCount == 4) {
		printLine("Choose a pattern for the map:");
		printLine("[1] Chords/Jack");
		print("[2] Jumpstream\n> ");
		patternChosen = getInt(1,2);
	}

	enum Pattern { UNDEFINED, CHORDS, JUMPSTREAM };
	Pattern pattern = (Pattern)patternChosen;

	//Create generator and options according to pattern type
	Generator* generator;
	std::string diffname;
	switch (pattern) {
	case CHORDS: {
		ChordOptions options(keyCount);
		options.presentOptions();
		diffname = options.getDiffname();
		std::vector<int> distributions = options.getDistributions();
		generator = new ChordGenerator(&distributions);
		break;
	}
	case JUMPSTREAM: {
		JumpstreamOptions options;
		options.presentOptions();
		diffname = options.getDiffname();
		int splitChordPercentage = options.getSplitChordPercentage();
		generator = new JumpstreamGenerator(splitChordPercentage);
		break;
	}
	default:
		printLine("Pattern selected is invalid, please reply with just the number 1 or 2");
		system("pause");
		exit(EXIT_FAILURE);
	}

	//default bpm set to -1 to signify no bpm specified
	int bpm = -1;

	//cap bpm
	printLine("Would you like to cap the bpm?(y/n): ");
	std::string answer = getString();
	if (answer != "n") {
		printLine("Enter the max bpm you want to appear as a whole number (Ex. 210).");
		printLine("High bpm + 1/8th notes usually makes impossible jacks in chord/jack patterns.");
		print("bpm> ");
		bpm = getInt(1, INT_MAX);
	}

	//convert file
	std::vector<std::string> originalHitObjects = grabHitObjects(filename);
	std::set<int> timestamps = getTimeStampSet(originalHitObjects, bpm);
	std::vector<std::string> generatedHitObjects = generator->generateHitObjects(timestamps, keyCount);
	std::vector<std::string> convert = convertFile(filename, generatedHitObjects, diffname);
	writeToFile(convert, filename, diffname);
}

std::string MainOptions::getDiffname() {
	return "_UNKOWN";
}