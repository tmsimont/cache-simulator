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

using namespace std;

class cache
{
public:
	cache();
	cache(cacheParameter para);

	bool hasAddress(address add);
	void write(address add);
	int getMissPenalty() { return missPenalty; }
	int getHitTime() { return hitTime; }

	~cache();

private:
	vector<cacheSet> sets;
	int numbBlocks;
	int numbSets;

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
