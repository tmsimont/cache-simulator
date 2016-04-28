#ifndef CACHEUPDATERRANDOM_H
#define CACHEUPDATERRANDOM_H
#include "CacheUpdater.h"

class CacheUpdaterRandom : public CacheUpdater {
public:
	CacheUpdaterRandom(cache * target) : CacheUpdater(target) {};
	std::vector<CacheEvent> writeToCache(address * addr);
	~CacheUpdaterRandom();
};
#endif // CACHEUPDATERRANDOM_H