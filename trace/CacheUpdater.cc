#include "CacheUpdater.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include "CacheParameters.h"

using std::vector;


cache * CacheUpdater::getCache()
{
	return targetCache;
}

CacheUpdater::~CacheUpdater()
{
}

CacheUpdater::CacheUpdater()
{
}


std::vector<CacheEvent> CacheUpdater::writeToCache(cacheParameters::writePolicy writePolicy, address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock = getBlockForReplacement(addr, targetSet);

	if (writePolicy == cacheParameters::writePolicy::BACK) {
		// todo: write back before replace
	}

	// adjust the block tag and valid bit
	address tag = address(targetCache->getTag(addr->getAddr()));
	targetBlock->validBit = true;
	targetBlock->addr = tag;

	return events;
}

CacheUpdater::CacheUpdater(cache * targetCache)
{
	this->targetCache = targetCache;
}

void CacheUpdater::hitCache(address * addr, int setIdx, int blockIdx)
{
	// nothing to do... unless this an special extended LRU
}