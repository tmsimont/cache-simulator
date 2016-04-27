/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheSet.cc
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>
#include <random>

#include "CacheSet.h"
#include "CacheBlock.h"
#include "Address.h"


using namespace std;

cacheSet::cacheSet()
{
	numbBlocks = 0;
}

cacheSet::cacheSet(int nB, int bS)
{
	numbBlocks = nB;
	blockSize = bS;
	blocks.resize(numbBlocks);
	for (int i = 0; i < numbBlocks; ++i)
	{
		blocks[i] = cacheBlock(blockSize);
	}

}

void cacheSet::writeAddress(address add)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, numbBlocks - 1);
	//confirm 0 <= i < blockSize

	generator.seed((unsigned int)time(nullptr));
	blocks[distribution(generator)].write(add);
}

bool cacheSet::inCacheSet(address add)
{
	bool in = false;
	for (int i = 0; i < numbBlocks && in == false; i++)
		in = blocks[i].inBlock(add);
	return in;
}

vector<cacheBlock> cacheSet::getCacheBlocks()
{
	return blocks;
}

cacheSet::~cacheSet()
{
}