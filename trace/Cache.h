/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: Cache.h
*/

#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <vector>

#include "CacheBlock.h"
#include "CacheSet.h"
#include "CacheParameters.h"
#include "Address.h"
#include <bitset>

using namespace std;

class cache
{
public:

	cache();
	cache(cacheParameters para);

	bool hasAddress(address add);
	int getMissPenalty() { return params.missPenalty; }
	int getHitTime() { return params.hitTime; }
	int getPriority() { return params.priority; }
	string getName() { return params.name; }
	cacheParameters::ReplacementPolicy getReplacementPolicy() { return params.replacementPolicy; }

	unsigned int indexSize;
	unsigned int offsetSize;
	unsigned int tagSize;
	unsigned int getTag(address ofAddress);
	unsigned int getIndex(address ofAddress);
	unsigned int getOffset(address ofAddress);
	int getAssociativity();
	
	cacheSet * getCacheSet(address forAddress);

	vector<cacheSet> sets;
	int numbBlocks;
	int numbSets;

	~cache();

private:
	cacheParameters params;
};

#endif // CACHE_H
