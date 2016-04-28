#ifndef CACHEUPDATERRANDOM_H
#define CACHEUPDATERRANDOM_H
#include "CacheUpdater.h"

class CacheUpdaterRandom : public CacheUpdater {
public:
	CacheUpdaterRandom(cache * target) : CacheUpdater(target) {};
	cacheBlock * getBlockForReplacement(address * addr, cacheSet* set);
	~CacheUpdaterRandom();
};
#endif // CACHEUPDATERRANDOM_H