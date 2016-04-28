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


std::vector<CacheEvent> CacheUpdater::writeToCache(InstructionSimulation * sim, address * addr)
{
	events = std::vector<CacheEvent>();

	// get set from cache based on address (cache will use index)
	cacheSet *targetSet = targetCache->getCacheSet(*addr);

	// determine target block
	cacheBlock * targetBlock = getBlockForReplacement(addr, targetSet);

	// todo: write back before replace
	if (sim->arch->writePolicy == cacheParameters::writePolicy::BACK) {
		// get next cache index
		int j = getCache()->getPriority() + 1; 
		// if next cache is not main memory...
		if (j < sim->arch->getNumbCaches()) {
			CacheUpdater *otherCacheUpdater = sim->getCacheUpdaterAtIndex(j);
			// todo: use CacheUpdater on other cache to write from THIS CACHE -> L(this + 1)
			// that updater does the same thing again, so all caches L(this) to main memory
			// are updated without a loop (chain of functions instead)
		}
		else {
			// main memory update
			sim->mainMemoryRead();
		}
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