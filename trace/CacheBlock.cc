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
	validBit = false;
	addr = address();
}

cacheBlock::cacheBlock(int bS)
{
	blockSize = bS;
	validBit = false;
	addr = address();
}

bool cacheBlock::inBlock(address ad)
{
	if (addr == ad && validBit)
		return true;
	return false;
}

cacheBlock::~cacheBlock()
{

}