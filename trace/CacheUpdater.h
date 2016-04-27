#ifndef CACHEUPDATER_H
#define CACHEUPDATER_H
#include "CacheEvent.h"
#include "Cache.h"
#include <vector>

class CacheUpdater {
public:
	CacheUpdater();
	CacheUpdater(cache* targetCache);
	virtual std::vector<CacheEvent> writeToCache(address * addr) = 0;
	void hitCache(address * addr, int setIdx, int blockIdx);
	cache * getCache();
protected:
	cache* targetCache;
	std::vector<CacheEvent> events;
};
#endif // CACHEUPDATER_H