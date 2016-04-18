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

//#define DEBUG 1

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
	uniform_int_distribution<int> distribution(0, numbBlocks);
	//confirm 0 <= i < blockSize
	
	
	//calculate which set to write to
	blocks[distribution(generator)].write(address(add.getAddr() >> (int)log(blockSize)));
}

bool cacheSet::inCacheSet(address add)
{
	bool in = false;

	#ifdef DEBUG
		cout << "checking for " << add.getAddr() << " in block " << add.getAddr() % numbBlocks << endl;
	#endif

	for (int i = 0; i < numbBlocks && in == false; i++)
		in = blocks[i].inBlock(address(add.getAddr() >> (int)log(blockSize)));

	return in;
}

vector<cacheBlock> cacheSet::getCacheBlocks()
{
	return blocks;
}

cacheSet::~cacheSet()
{
}