#pragma once
#include <vector>
#include <string>
#include <set>
#include <utility>

class Generator
{
public:
//Undefined function that all generators must override 
	virtual std::vector<std::string> generateHitObjects(std::set<int> timeStamps, int keyCount) = 0;


//Some helper functions
	
	//Used to create a hit object aka a note in osu file format 
	std::string convertToHitObject(int timeStamp, int columnNumber, int keyCount);

	//generates a rand pair of ints that are adjacent, Ex. (2,3)
	std::pair<int, int> getAdjacentPair(int a, int b, int exclude = -1);
	//generates a rand pair of ints that are non-adjacent, Ex. (1,3)
	std::pair<int, int> getNonAdjacentPair(int a, int b, int exclude = -1);

	//true if the pair contains x
	bool contains(std::pair<int, int> p, int x);

	//calculate distance between notes, Ex. distance(1,3) = 2
	int distance(int a, int b);

	//Generate random boolean that is less likely to be a certain outcome
	//the more that outcome happens in succession
	bool randomWithSway(bool last, int& sway);

	//Calculate a number to indicate hand usage, higher number means less balanced
	int calculateHandUsage(std::vector<std::set<int>> notes);

	//Not completely random, made for BracketGenerator but later used for LayeredStairs
	std::set<int> getRandomStart();
};

