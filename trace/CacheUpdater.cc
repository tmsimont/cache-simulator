#include "CacheUpdater.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include "CacheParameters.h"
#include <random>
#include <iomanip>

using std::vector;

std::vector<CacheEvent> CacheUpdater::writeToCache(address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);
	
	// determine target block
	cacheBlock * targetBlock;
	switch (targetCache->getReplacementPolicy()) {
		case cacheParameters::ReplacementPolicy::LRU:

			break;

		case cacheParameters::ReplacementPolicy::RANDOM:
		default:
			default_random_engine generator;
			uniform_int_distribution<int> distribution(0, targetSet->numbBlocks - 1);
			generator.seed((unsigned int)time(nullptr));
			targetBlock = &(targetSet->blocks[distribution(generator)]);
			break;
	}
		
	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}

cache * CacheUpdater::getCache()
{
	return targetCache;
}

CacheUpdater::CacheUpdater()
{
}

CacheUpdater::CacheUpdater(cache * targetCache)
{
	this->targetCache = targetCache;
}
