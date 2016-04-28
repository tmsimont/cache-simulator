#ifndef CACHEUPDATER_H
#define CACHEUPDATER_H
#include "CacheEvent.h"
#include "CacheParameters.h"
#include "Cache.h"
#include <vector>

class CacheUpdater {
public:
	CacheUpdater();
	CacheUpdater(cache* targetCache);
	std::vector<CacheEvent> writeToCache(cacheParameters::writePolicy writePolicy, address * addr);
	virtual cacheBlock * getBlockForReplacement(address * addr, cacheSet* set) = 0;
	void hitCache(address * addr, int setIdx, int blockIdx);
	cache * getCache();
	// virtual destructor http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
	virtual ~CacheUpdater();
protected:
	cache* targetCache;
	std::vector<CacheEvent> events;
};
#endif // CACHEUPDATER_H