#include "StreamOptions.h"

void StreamOptions::presentOptions() {
	diffname = askForDiffname(diffname);
}

std::string StreamOptions::getDiffname() {
	return diffname;
}