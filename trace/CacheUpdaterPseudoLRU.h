#ifndef CACHEUPDATERPSEUDOLRU_H
#define CACHEUPDATERPSEUDOLRU_H
#include "CacheUpdater.h"
#include <vector>

class CacheUpdaterPseudoLRU : public CacheUpdater {
public:
	CacheUpdaterPseudoLRU(cache * target);
	cacheBlock * getBlockForReplacement(address * addr, cacheSet* set);
	void hitCache(address * addr, int setIdx, int blockIdx);

	// pseudo-lru special members
	vector<vector<bool>> nWayBits;
	void recordUse(int setIdx, int blockIdx);
	~CacheUpdaterPseudoLRU();

};
#endif // CACHEUPDATERPSEUDOLRU_H
