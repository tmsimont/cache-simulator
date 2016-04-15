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
	blocksSize = bS;
	blocks.resize(numbBlocks);
	for (int i = 0; i < numbBlocks; ++i)
	{
		blocks[i] = new cacheBlock(blockSize);
	}

}

void cacheSet::writeAddress(address add)
{
	int i = add.getIndex();
	//confirm 0 <= i < blockSize
	//calculate which set to write to
	blocks[i].write(add);
}

bool cacheSet::inCacheSet(address add)
{
	bool in = false;
	int i = 0;

	while((i < numbBlocks) && !in)
	{
		in = blocks[i].inBlock(add);
		++i;
	}

	return in;
}

CacheSet::~CacheSet()
{
	erase blocks;
}