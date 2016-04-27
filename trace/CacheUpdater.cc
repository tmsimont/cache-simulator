#include "CacheUpdater.h"
#include "CacheSet.h"
#include "CacheBlock.h"
#include "CacheParameters.h"

using std::vector;


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

void CacheUpdater::hitCache(address * addr)
{
	// nothing to do... unless this an special extended LRU
}