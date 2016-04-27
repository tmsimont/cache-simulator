#ifndef CACHEUPDATERLRU_H
#define CACHEUPDATERLRU_H
#include "CacheUpdater.h"

class CacheUpdaterLRU : public CacheUpdater {
public:
	CacheUpdaterLRU(cache * target) : CacheUpdater(target) {};
	std::vector<CacheEvent> writeToCache(address * addr);
	void hitCache(address * addr);
};
#endif // CACHEUPDATERLRU_H