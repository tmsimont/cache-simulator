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

//#define DEBUG 1

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
	#ifdef DEBUG
		cout << "InBlock, myaddr: " << addr.getAddr() << ", check addr: " << ad.getAddr() << ", valid: " << (validBit == true ? "1" : "0") << " in " << this << endl;
	#endif
	if (addr == ad && validBit)
		return true;
	return false;
}

void cacheBlock::write(address ad)
{
	#ifdef DEBUG
		cout << "setting valid bit and addr to " << ad.getAddr() << " in " << this << endl;
	#endif
	this->validBit = true;
	this->addr = ad;
}

cacheBlock::~cacheBlock()
{

}