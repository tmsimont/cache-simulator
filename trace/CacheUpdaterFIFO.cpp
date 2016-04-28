#include "CacheUpdaterFIFO.h"

std::vector<CacheEvent> CacheUpdaterFIFO::writeToCache(address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock;

	// todo: implement FIFO (see CacheUpdaterPseudoLRU.h and CacheUpdaterPseudoLRU.cc for inspiration...)
	targetBlock = &(targetSet->blocks[0]);

	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}

CacheUpdaterFIFO::~CacheUpdaterFIFO()
{
}
