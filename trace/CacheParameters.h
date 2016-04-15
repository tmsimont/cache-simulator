/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheParameters.h
*/

#ifndef CACHEPARAMETERS_H
#define CACHEPARAMETERS_H

#include <string>
#include <vector>


using namespace std;

class cacheParameters
{
public:
	cacheParameters()
	{ priority = 0, blockSize = 0, name = "", size = 0, associativity = 0, missPenalty = 0, hitTime = 0; }
	cacheParameters(int pr, int bS, string na, int si, int as, int mP, int hT) 
	{ priority = pr, blockSize = bS, name = na, size = si, associativity = as, missPenalty = mP, hitTime = hT; }

	int getPriority() { return priority; }
	int getBlockSize() { return blockSize; }
	string getName() { return name; }
	int getSize() { return size; }
	int getAssociativity() { return associativity; }
	int getMissPenalty() { return missPenalty; }
	int getHitTime() { return hitTime; }

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

#endif // CACHEARCHITECTURE_H
