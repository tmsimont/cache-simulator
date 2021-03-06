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
#define ADDRESS_SIZE 32
#define FULL_ASSOC 0

using namespace std;

cache::cache()
{

}

cache::cache(cacheParameters para)
{
	this->params = para;
	
	numbBlocks = params.size / params.blockSize;
	numbSets = para.associativity != FULL_ASSOC ? numbBlocks / params.associativity : 1;

	indexSize = log2(numbSets);
	offsetSize = log2(params.blockSize);
	tagSize = (ADDRESS_SIZE - indexSize - offsetSize);

	sets.resize(numbSets);

	for (int i = 0; i < numbSets || (i == 0 && numbSets == FULL_ASSOC); ++i)
	{
		sets[i] = cacheSet(params.associativity != FULL_ASSOC?params.associativity:numbBlocks, params.blockSize);
	}

}

bool cache::hasAddress(address add) {
	return sets[getIndex(add)].inCacheSet(add);
}

cacheSet * cache::getCacheSet(address add) {
	return &(sets[getIndex(add)]);
}

unsigned int cache::getTag(address ofAddress) {
	// tag is first bunch of address bits, so just shift off the index and offset bits
	return ofAddress.getAddr() >> (indexSize + offsetSize);
}

unsigned int cache::getIndex(address ofAddress) {
	// get a mask 0000000011000000 where the one's are sandwiched by 0's for tag and 0's for offset
	unsigned int mask = ((1 << (indexSize)) - 1) << (offsetSize);
	return (ofAddress.getAddr() & mask) >> (offsetSize);
}

unsigned int cache::getOffset(address ofAddress) {
	// offset is offsetSize number of bits at end of address
	unsigned int mask = (1 << (offsetSize + 1)) - 1;
	return (ofAddress.getAddr() & mask);
}

int cache::getAssociativity() { 
	return params.associativity == FULL_ASSOC? numbBlocks : params.associativity; 
}

cache::~cache()
{
}
