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

	cout << "num blocks: " << numbBlocks << endl;
	for (int i = 0; i < numbBlocks; ++i)
	{
		blocks[i] = cacheBlock(blockSize);
	}
	cout << "end num blocks" << endl;

}

void cacheSet::writeAddress(address add)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, numbBlocks);
	//confirm 0 <= i < blockSize
	//calculate which set to write to
	blocks[distribution(generator)].write(add);
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

cacheSet::~cacheSet()
{

}