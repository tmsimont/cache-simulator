#ifndef CACHEUPDATERLRU_H
#define CACHEUPDATERLRU_H
#include "CacheUpdater.h"

class CacheUpdaterLRU : public CacheUpdater {
public:
	CacheUpdaterLRU(cache * target) : CacheUpdater(target) {};
	cacheBlock * getBlockForReplacement(address * addr, cacheSet* set);
	void hitCache(address * addr, int setIdx, int blockIdx);
	~CacheUpdaterLRU();
};
#endif // CACHEUPDATERLRU_H