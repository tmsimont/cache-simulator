#ifndef CACHEUPDATERFIFO_H
#define CACHEUPDATERFIFO_H
#include "CacheUpdater.h"

class CacheUpdaterFIFO : public CacheUpdater {
public:
	CacheUpdaterFIFO(cache * target) : CacheUpdater(target) {};
	std::vector<CacheEvent> writeToCache(address * addr);
	~CacheUpdaterFIFO();
};
#endif // CACHEUPDATERFIFO_H