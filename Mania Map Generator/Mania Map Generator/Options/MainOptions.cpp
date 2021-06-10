//options
#include "Options.h"
#include "MainOptions.h"
#include "ChordOptions.h"
#include "JumpstreamOptions.h"
#include "HandstreamOptions.h"
#include "BracketOptions.h"
#include "StreamOptions.h"
#include "LayeredStairsOptions.h"
//generators
#include "Generator.h"
#include "ChordGenerator.h"
#include "JumpstreamGenerator.h"
#include "HandstreamGenerator.h"
#include "BracketGenerator.h"
#include "StreamGenerator.h"
#include "LayeredStairsGenerator.h"
//other
#include "FileHandler.h"
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
		printLine("[2] Jumpstream");
		printLine("[3] Handstream");
		printLine("[4] Brackets");
		print("[5] Single stream\n > ");

		patternChosen = getInt(1,5);
	}
	else if (keyCount == 7) {
		printLine("Choose a pattern for the map:");
		printLine("[1] Chords/Jack");
		printLine("[2] Brackets");
		print("[3] Layered Stairs\n> ");

		patternChosen = getInt(1, 3);
	}

	enum Pattern { UNDEFINED, CHORDS, JUMPSTREAM, HANDSTREAM, BRACKETS, SINGLESTREAM, LAYERED_STAIRS };
	Pattern pattern = (Pattern)patternChosen; //casting works if its 4k
	if (keyCount == 7) {
		switch (patternChosen) {
			case 1:  pattern = CHORDS; break;
			case 2:  pattern = BRACKETS; break;
			case 3:  pattern = LAYERED_STAIRS; break;
			default: pattern = CHORDS; break;
		}
	}

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
	case HANDSTREAM: {
		HandstreamOptions options;
		options.presentOptions();
		diffname = options.getDiffname();
		int splitChordPercentage = options.getSplitChordPercentage();
		generator = new HandstreamGenerator(splitChordPercentage);
		break;
	}
	case BRACKETS: {
		BracketOptions options(keyCount);
		options.presentOptions();
		diffname = options.getDiffname();
		int missingPercentage = options.getMissingPercentage();
		int useGenerator = options.getGenerator();
		if (keyCount == 7 and useGenerator == 2) {
			generator = new LayeredStairsGenerator(std::rand() % 2 + 3);
		}
		else {
			generator = new BracketGenerator(missingPercentage);
		}
		break;
	}
	case SINGLESTREAM: {
		StreamOptions options;
		options.presentOptions();
		diffname = options.getDiffname();
		int trillPercentage = options.getTrillPercentage();
		generator = new StreamGenerator(trillPercentage);
		break;
	}
	case LAYERED_STAIRS: {
		LayeredStairsOptions options;
		options.presentOptions();
		diffname = options.getDiffname();
		int stairCount = options.getStairCount();
		generator = new LayeredStairsGenerator(stairCount);
		break;
	}
	default:
		printLine("Pattern selected is invalid. Report this if you think it is a bug.");
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
	if (generatedHitObjects.empty()) {
		printLine("Conversion unsuccessful");
		system("pause");
		exit(EXIT_FAILURE);
	}
	std::vector<std::string> convert = convertFile(filename, generatedHitObjects, diffname);
	writeToFile(convert, filename, diffname);
}

std::string MainOptions::getDiffname() {
	return "_UNKNOWN";
}