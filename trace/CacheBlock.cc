/* Author: Cory Linfield, Trevor Simonton, Rania Abdraba, and Anthony Pfaff
Course: CSCI 5593
Project: Semester Project Implementation
File: CacheBlock.cc
*/

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <iterator>
#include <stdlib.h>

#include "CacheBlock.h"
#include "Address.h"

using namespace std;

cacheBlock::cacheBlock()
{
	blockSize = 0;
}

cacheBlock::cacheBlock(int bS)
{
	blockSize = bS;
	slots.resize(blockSize);
	filled = 0;
}

bool cacheBlock::inBlock(address ad)
{
	bool in = false;
	int i = 0;

	while ((i < blockSize) && !in)
	{
		if (slots[i] == ad)
			in = true;

		++i;
	}

	return in;
}

void write(address ad)
{
	if (filled < blockSize)			//if slots in block are not filled, write to empty slot
	{
		slots[filled] = ad;
		++filled;
	}
	else							//if slots in block are filled, evict one of addresses (currently this is random)
	{
		int r = rand() % blockSize;
		slots[r] = ad;
	}
}

cacheBlock::~cacheBlock()
{
	erase slots;
}