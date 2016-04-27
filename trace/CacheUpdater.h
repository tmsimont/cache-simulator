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
	cache * getCache();
private:
	cache* targetCache;
	std::vector<CacheEvent> events;
};
#endif // CACHEUPDATER_H