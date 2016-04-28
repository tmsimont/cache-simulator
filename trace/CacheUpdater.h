#ifndef CACHEUPDATER_H
#define CACHEUPDATER_H
#include "CacheEvent.h"
#include "Cache.h"
#include <vector>

class CacheUpdater {
public:
	CacheUpdater();
	CacheUpdater(cache* targetCache);
	std::vector<CacheEvent> writeToCache(address * addr);
	virtual cacheBlock * getBlockForReplacement(address * addr, cacheSet* set) = 0;
	void hitCache(address * addr, int setIdx, int blockIdx);
	cache * getCache();
	bool evictedDirtyBlock() { return _evictedDirtyBlock; };
	// virtual destructor http://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
	virtual ~CacheUpdater();
protected:
	cache* targetCache;
	std::vector<CacheEvent> events;
	bool _evictedDirtyBlock;
};
#endif // CACHEUPDATER_H