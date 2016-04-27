#include "CacheUpdaterRandom.h"
#include <random>
#include <iomanip>

std::vector<CacheEvent> CacheUpdaterRandom::writeToCache(address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, targetSet->numbBlocks - 1);
	generator.seed((unsigned int)time(nullptr));
	targetBlock = &(targetSet->blocks[distribution(generator)]);

	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}
