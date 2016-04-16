/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: Cache.cc
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>

#include "Cache.h"
#include "CacheBlock.h"
#include "CacheSet.h"
#include "CacheParameters.h"
#include "Address.h"

//#define DEBUG 1

using namespace std;

cache::cache()
{

}

cache::cache(cacheParameters para)
{
	priority = para.getPriority();
	blockSize = para.getBlockSize();
	name = para.getName();
	size = para.getSize();
	associativity = para.getAssociativity();
	missPenalty = para.getMissPenalty();
	hitTime = para.getHitTime();
	
	numbBlocks = size / blockSize;
	numbSets = numbBlocks / associativity;

	sets.resize(numbSets);
	for (int i = 0; i < numbSets; ++i)
	{
		sets[i] = cacheSet(numbBlocks, blockSize);
	}
	
}

bool cache::hasAddress(address add)
{					// currently looking through every set - should fix to look in correct set first
	bool inCache = false;
	int i = 0;

	for (int i = 0; i < associativity && inCache == false; i++)
	{
	#ifdef DEBUG
			cout << "in set " << ((add.getAddr() >> (int)log(size)) % associativity) + i << endl;
	#endif
		inCache = sets[((add.getAddr() >> (int)log(size)) % associativity) + i].inCacheSet(address(add.getAddr() >> (int)log(size)));
	}

	return inCache;
}

void cache::write(address add)
{
	//int i = add.getIndex();
	//confirm 0 <= i < numbSets
	//calculate which set to write to

	//TODO: free this to write to write to any of the available sets

	sets[((add.getAddr() >> (int)log(size)) % associativity)].writeAddress(address(add.getAddr() >> (int)log(size)));
}

cache::~cache()
{

}