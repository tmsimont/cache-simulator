#include "CacheUpdaterLRU.h"

cacheBlock * CacheUpdaterLRU::getBlockForReplacement(address * addr, cacheSet * set)
{
	// todo: implement LRU (see CacheUpdaterPseudoLRU.h and CacheUpdaterPseudoLRU.cc for inspiration...)
	return &(set->blocks[0]);
}

void CacheUpdaterLRU::hitCache(address * addr, int setIdx, int blockIdx)
{
}

CacheUpdaterLRU::~CacheUpdaterLRU()
{
}
