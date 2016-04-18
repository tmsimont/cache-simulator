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
#include <random>

#include "Cache.h"
#include "CacheBlock.h"
#include "CacheSet.h"
#include "CacheParameters.h"
#include "Address.h"

#define DEBUG 1

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
		sets[i] = cacheSet(associativity, blockSize);
	}
	
	#ifdef DEBUG
		cout << "Cache " << name << ", priority: " << priority << ", " << "block size: " << blockSize << ", " << "assoc: " << associativity << ", " << " size: " << size << ", numBlocks: " << numbBlocks << ", " << " numSets: " << numbSets << endl;
	#endif
}

bool cache::hasAddress(address add)
{					// currently looking through every set - should fix to look in correct set first
	bool inCache = false;
	int i = 0;

	for (int i = 0; i < associativity && inCache == false; i++)
	{
	//#ifdef DEBUG
	//		cout << "in set " << ((add.getAddr() >> (int)log(size)) % associativity) + i << endl;
	//#endif
		inCache = sets[(add.getAddr() % numbSets) + i].inCacheSet(add);
	}

	return inCache;
}

void cache::write(address add)
{
	//int i = add.getIndex();
	//confirm 0 <= i < numbSets
	//calculate which set to write to

	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, associativity - 1);
	//confirm 0 <= i < blockSize


	//calculate which set to write to

	sets[add.getAddr() % numbSets + distribution(generator)].writeAddress(address(add.getAddr()));
}

cache::~cache()
{

}