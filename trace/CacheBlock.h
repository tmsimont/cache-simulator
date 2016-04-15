/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheBlock.h
*/

#ifndef CACHEBLOCK_H
#define CACHEBLOCK_H

#include <string>
#include <vector>
#include <bitset>

#include "Address.h"

using namespace std;

class cacheBlock
{
public:
	cacheBlock();
	cacheBlock(int bS);
	bool inBlock(address ad);
	void write(address ad);
	
private:
	bit validBit;
	bitset tag;
	bitset contents;
	vector<address> slots;
	int blockSize;
	int filled;
};

#endif // CACHEBLOCK_H
