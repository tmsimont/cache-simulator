#ifndef CACHEUPDATERPSEUDOLRU_H
#define CACHEUPDATERPSEUDOLRU_H
#include "CacheUpdater.h"

class CacheUpdaterPseudoLRU : public CacheUpdater {
public:
	CacheUpdaterPseudoLRU(cache * target) : CacheUpdater(target) {};
	std::vector<CacheEvent> writeToCache(address * addr);
	void hitCache(address * addr);
};
#endif // CACHEUPDATERPSEUDOLRU_H