#ifndef CACHEUPDATER_H
#define CACHEUPDATER_H
#include "CacheEvent.h"
#include "Cache.h"
#include <vector>

class CacheUpdater {
public:
	std::vector<CacheEvent> writeToCache(cache* target, address * addr);
private:
	cache* targetCache;
	std::vector<CacheEvent> events;
};
#endif // CACHEUPDATER_H