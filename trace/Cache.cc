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

	cout << "num sets: " << numbSets << endl;

	indexSize = log2(numbSets);
	offsetSize = log2(blockSize);
	tagSize = (ADDRESS_SIZE - indexSize - offsetSize);

	sets.resize(numbSets);
	for (int i = 0; i < numbSets; ++i)
	{
		sets[i] = cacheSet(associativity, blockSize);
	}
	
	#ifdef DEBUG
		cout << "Cache " << name << ", priority: " << priority << ", " << "block size: " << blockSize << ", " << "assoc: " << associativity << ", " << " size: " << size << ", numBlocks: " << numbBlocks << ", " << " numSets: " << numbSets << endl;
	#endif
}

bool cache::hasAddress(address add) {
	return sets[getIndex(add)].inCacheSet(add);
}

cacheSet cache::getCacheSet(int index) {
	return sets[index];
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

cache::~cache()
{

}