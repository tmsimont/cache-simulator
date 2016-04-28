#ifndef CACHEUPDATERPSEUDOLRU_H
#define CACHEUPDATERPSEUDOLRU_H
#include "CacheUpdater.h"
#include <vector>

class CacheUpdaterPseudoLRU : public CacheUpdater {
public:
	CacheUpdaterPseudoLRU(cache * target);
	std::vector<CacheEvent> writeToCache(address * addr);
	void hitCache(address * addr, int setIdx, int blockIdx);

	// pseudo-lru special members
	vector<vector<bool>> nWayBits;
	void recordUse(int setIdx, int blockIdx);

};
#endif // CACHEUPDATERPSEUDOLRU_H
