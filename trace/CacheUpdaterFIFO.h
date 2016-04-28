#ifndef CACHEUPDATERFIFO_H
#define CACHEUPDATERFIFO_H
#include "CacheUpdater.h"

class CacheUpdaterFIFO : public CacheUpdater {
public:
	CacheUpdaterFIFO(cache * target) : CacheUpdater(target) {};
	cacheBlock * getBlockForReplacement(address * addr, cacheSet* set);
	~CacheUpdaterFIFO();
};
#endif // CACHEUPDATERFIFO_H