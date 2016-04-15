/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheSet.h
*/

#ifndef CACHESET_H
#define CACHESET_H

#include <string>
#include <vector>

#include "Address.h"
#include "CacheBlock.h"

using namespace std;

class cacheSet
{
public:
	cacheSet();
	cacheSet(int nB, int bS);
	void writeAddress(address add);
	bool inCacheSet(address add);

	~cacheSet();
private:
	int numbBlocks;
	int blocksSize;
	vector<cacheBlock> blocks;


};

#endif // CACHESET_H
