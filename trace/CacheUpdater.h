#pragma once
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