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
	void write(address add);
	int getMissPenalty() { return missPenalty; }
	int getHitTime() { return hitTime; }
	string getName() { return name; }


	unsigned int indexSize;
	unsigned int offsetSize;
	unsigned int tagSize;
	unsigned int getTag(address ofAddress);
	unsigned int getIndex(address ofAddress);
	unsigned int getOffset(address ofAddress);
	
	cacheSet getCacheSet(int index);

	vector<cacheSet> sets;
	int numbBlocks;
	int numbSets;

	~cache();

private:


	int priority;
	int blockSize;
	string name;
	int size;
	int associativity;
	//bool hasWriteBuffer;
	//bool hasVictimBuffer;
	//enum replacementPolicy;
	int missPenalty;
	int hitTime;
};

#endif // CACHE_H
