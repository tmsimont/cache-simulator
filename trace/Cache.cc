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

using namespace std;

chace::cache()
{

}

cache::cache(cacheParameter para)
{
	priority = para.getPriority();
	blockSize = para.getBlockSize();
	name = para.getName();
	size = para.getSize();
	associativity = para.getAssociativity();
	missPenalty = para.missPenalty();
	hitTime = para.hitTime();
	
	numbBlocks = size / blockSize;
	numbSets = numbBlocks / associativity;

	sets.resize(numbSets);
	for (int i = 0; i < numbSets; ++i)
	{
		sets[i] = new cache(numbBlocks, blockSize);
	}
	
}

bool cache::hasAddress(address add)
{					// currently looking through every set - should fix to look in correct set first
	bool inCache = false;
	int i = 0;

	while ((i < numbSets) && (!inCache))
	{
		inCache = sets[i].hasAddress(add);
		++i;
	}

	return inCache;
}

void cache::write(address add)
{
	int i = add.getIndex();
	//confirm 0 <= i < numbSets
	//calculate which set to write to
	sets[i].writeAddress(add);
}

cache::~cache()
{
	erase sets;
}