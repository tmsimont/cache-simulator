#pragma once
#include "CacheEvent.h"
#include "CacheSearch.h"
#include "CacheUpdater.h"
#include "Cache.h"
#include "Address.h"
#include <vector>
#include <string>

using std::vector;
class InstructionSimulation {
public:
	virtual void hitCache(cache* cache) = 0;
	virtual void missCache(cache* cache) = 0;
	virtual void writeForward(cache* cache) = 0;

	void mainMemoryRead();
	void reportEvent(std::string e);
	vector<CacheEvent> simulate(cacheArchitecture* arch, address* add);
protected:
	address* add;
	cacheArchitecture* arch;
	cache* getCacheAtIndex(int i);

	// reporting
	int time;
	vector<CacheEvent> events;
};
