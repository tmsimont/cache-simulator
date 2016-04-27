#include "CacheUpdater.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include <random>
#include <iomanip>

using std::vector;

std::vector<CacheEvent> CacheUpdater::writeToCache(cache * target, address * addr)
{
	events = std::vector<CacheEvent>();
	targetCache = target;

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);
	
	// random block from set
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, targetSet->numbBlocks - 1);
	generator.seed((unsigned int)time(nullptr));
	cacheBlock * targetBlock = &(targetSet->blocks[distribution(generator)]);
		
	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}
