#pragma once
#include "CacheEvent.h"
#include "CacheSearch.h"
#include "CacheUpdater.h"
#include "Cache.h"
#include "Address.h"
#include <vector>

using std::vector;
class InstructionSimulation {
public:
	virtual void hitCache(cache* cache);
	virtual void missCache(cache* cache);
	virtual void writeForward(cache* cache);

	void mainMemoryRead();
	vector<CacheEvent> simulate(cacheArchitecture* arch, address* add);
protected:
	cache* getCacheAtIndex(int i);
	int time;
	address* add;
	cacheArchitecture* arch;
};
