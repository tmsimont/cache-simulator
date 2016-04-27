#pragma once
#include "CacheEvent.h"
#include "CacheSearch.h"
#include "CacheUpdater.h"
#include "Cache.h"
#include "Address.h"
#include <vector>
#include <string>

using std::vector;

/**
 * Base class for individual instruction simulation functions.
 * The base class encapsulates the basic L1 to LN pattern that 
 * is repeated for all instruction simulations
 * @see: InstructionSimulation::simulate
 *
 * The base class also provides a central "reportEvent" function
 * to handle events that arise during simulation
 * @see InstructionSimulation::reportEvent
 *
 * Derived classes can provide specific functions
 * for how to handle hits on caches, misses on caches and
 * write forwards, as well as how to get a cache at an index
 * from the architecture (for instruction cache)
 *
 */
class InstructionSimulation {
public:
	virtual void hitCache(cache* cache) = 0;
	virtual void missCache(cache* cache) = 0;
	virtual void writeForward(cache* cache) = 0;

	void mainMemoryRead();
	void reportEvent(std::string e);
	vector<CacheEvent> simulate(CacheSearch * finder, CacheUpdater * updater, cacheArchitecture* arch, address* add);

	int getTime();
protected:

	CacheSearch * finder;
	CacheUpdater * updater;

	cache* getCacheAtIndex(int i);

	// reporting
	cacheArchitecture* arch;
	address* add;
	int time;
	cache* currentCache;
	cache* previousCache;
	vector<CacheEvent> events;
};
