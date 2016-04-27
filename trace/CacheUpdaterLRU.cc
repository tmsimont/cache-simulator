#include "CacheUpdaterLRU.h"

std::vector<CacheEvent> CacheUpdaterLRU::writeToCache(address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock;

	// todo: implement LRU (see CacheUpdaterPseudoLRU.h and CacheUpdaterPseudoLRU.cc for inspiration...)
	targetBlock = &(targetSet->blocks[0]);

	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}

void CacheUpdaterLRU::hitCache(address * addr, int setIdx, int blockIdx)
{
}
