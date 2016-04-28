#include "CacheUpdaterFIFO.h"

cacheBlock * CacheUpdaterFIFO::getBlockForReplacement(address * addr, cacheSet * set)
{
	// todo: implement FIFO (see CacheUpdaterPseudoLRU.h and CacheUpdaterPseudoLRU.cc for inspiration...)
	return &(set->blocks[0]);
}

CacheUpdaterFIFO::~CacheUpdaterFIFO()
{
}
