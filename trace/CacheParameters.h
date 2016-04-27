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
	static enum ReplacementPolicy {
		RANDOM,
		LRU
	};

	int priority;
	int blockSize;
	string name;
	int size;
	int associativity;
	//bool hasWriteBuffer;
	//bool hasVictimBuffer;
	ReplacementPolicy replacementPolicy;
	int missPenalty;
	int hitTime;

};

#endif // CACHEARCHITECTURE_H
