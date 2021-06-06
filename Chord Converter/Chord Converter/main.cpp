#include "MainOptions.h"

int main() {
	MainOptions mainMenu;
	mainMenu.presentOptions();
	return 0;

	////have user select file
	//std::string filename = getOsuFile();
	//if (filename.empty()) {
	//	std::cout << "An error occured when selecting the file." << std::endl;
	//	system("pause");
	//	return 0;
	//}

	////get key count
	//std::vector<std::string> filedata = getLines(filename);
	//int keyCount = getKeyMode(filedata);

	////resolve pattern type
	//char c = '1';
	//if (keyCount == 4) {
	//	std::cout << "Choose a pattern for the map:\n"
	//			  << "[1] Chords/Jack\n"
	//			  << "[2] Jumpstream\n> " << std::endl;
	//	std::cin >> c;
	//}

	//enum Pattern { UNDEFINED, CHORDS, JUMPSTREAM };
	//Pattern pattern;
	//switch (c) {
	//case '1': pattern = CHORDS; break;
	//case '2': pattern = JUMPSTREAM; break;
	//default : pattern = UNDEFINED; break;
	//}

	////prompt for custom diffname
	//std::cout << "Want a custom diff name?(y/n): " << std::endl;
	//std::cin >> c;
	//std::string diffname;

	//// specified in larger scope to be used later
	//std::vector<int> distributions; 
	//int splitChordPercentage = 33;

	////Chords/Jack
	//if (pattern == CHORDS) {
	//	//resolve diff name of convert
	//	diffname = "CHORDS";
	//	if (c != 'n') {
	//		std::cout << "Enter diff name: " << std::endl;
	//		std::cin.ignore();
	//		std::getline(std::cin, diffname);
	//	}
	//	//prompt for detailed options
	//	std::cout << "Would you like to specify chord distributions?(y/n): " << std::endl;
	//	std::cin >> c;

	//	//set up default distributions
	//	for (int i = 0; i < keyCount - 1; i++) {
	//		distributions.push_back(100 / keyCount);
	//	}
	//	distributions.push_back(100 - (100 / keyCount * (keyCount - 1)));

	//	//if user chose to specify distributions, then prompt for chord size distributions
	//	if (c != 'n') {
	//		std::cout << "Enter whole numbers between 0-100.\n"
	//			<< "They are the percentages that a given chord size will appear.\n"
	//			<< "Totals over 100% may result in errors." << std::endl;
	//		for (int i = 0; i < keyCount; i++) {
	//			std::cout << "Chords size " << i + 1 << ": ";
	//			int n;
	//			std::cin >> n;
	//			if (n > 100 or n < 0) n = 0;
	//			distributions[i] = n;
	//		}
	//	}
	//}
	//else if (pattern == JUMPSTREAM) {
	//	//resolve diff name of convert
	//	diffname = "JUMPSTREAM";
	//	if (c != 'n') {
	//		std::cout << "Enter diff name: " << std::endl;
	//		std::cin.ignore();
	//		std::getline(std::cin, diffname);
	//	}

	//	//prompt for detailed options
	//	std::cout << "Split chords:\n"
	//		<< "A split chord is a chord with non-adjacent notes, like this pattern for example\n"
	//		<< "#  #\n"
	//		<< " #  \n"
	//		<< "# # \n"
	//		<< "   #\n"
	//		<< "# # \n" << std::endl;
	//	std::cout << "Would you like to specify split chord chance, default is 33%?(y/n): " << std::endl;
	//	std::cin >> c;
	//	
	//	//if user chose to specify distributions, then prompt for chord size distributions
	//	if (c != 'n') {
	//		std::cout << "Enter a whole number between 0-100.\n"
	//				  << "It is the percentage that a split chord will appear.\n" 
	//			      << "Low = more jack based and high = more messy" << std::endl;
	//		std::cin >> splitChordPercentage;
	//	}
	//}
	//else {
	//	std::cout << "Pattern selected is invalid, please reply with just the number 1 or 2" << std::endl;
	//	return 0;
	//}
	//
	////default bpm set to -1 to signify no bpm specified
	//int bpm = -1;

	////cap bpm
	//std::cout << "Would you like to cap the bpm?(y/n): " << std::endl;
	//std::cin >> c;
	//if (c != 'n') {
	//	std::cout << "Enter the max bpm you want to appear as a whole number (Ex. 210).\n"
	//		      << "High bpm + 1/8th notes usually makes impossible jacks in chord/jack patterns.\n";
	//	std::cout << "bpm> ";
	//	std::cin >> bpm;
	//}

	////convert file
	//std::vector<std::string> originalHitObjects = grabHitObjects(filename);
	//std::set<int> timestamps = getTimeStampSet(originalHitObjects, bpm);
	//std::vector<std::string> generatedHitObjects;

	//switch (pattern) {
	//	case CHORDS     : generatedHitObjects = createChartsHitObjects(timestamps, keyCount, distributions); break;
	//	case JUMPSTREAM : generatedHitObjects = createJumpStreamChart(timestamps, keyCount, splitChordPercentage); break;
	//}

	//std::vector<std::string> convert = convertFile(filename, generatedHitObjects, diffname);

	//writeToFile(convert, filename, diffname);

	//return 0;
}