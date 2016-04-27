#pragma once
#include "InstructionSimulation.h"
#include <iostream>

vector<CacheEvent> InstructionSimulation::simulate(cacheArchitecture* arch, address* add)
{
	this->arch = arch;
	this->add = add;

	int i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();
	CacheUpdater updater = CacheUpdater();

	// search L1 out to LN caches
	while ((i < arch->getNumbCaches()) && (!found))
	{
		// get a pointer to this cache (might be instruction...)
		cache* cache = getCacheAtIndex(i);

		// search the cache
		found = finder.cacheHasAddress(*cache, *add);

		if (found)
		{
			hitCache(cache);

			// write forward to LN down to L1
			for (i = i - 1; i >= 0; i--)
			{
				writeForward(cache);
			}
		}
		else
		{
			missCache(cache);
		}
		++i;
	}

	// no caches have the address
	if (!found)
	{
		mainMemoryRead();

		// write forward from main memory to LN to L1
		for (i = arch->getNumbCaches() - 1; i >= 0; --i)
		{
			cache* cache = arch->getCache(i);
			writeForward(cache);
		}
	}

	return vector<CacheEvent>();
}


cache* InstructionSimulation::getCacheAtIndex(int i) {
	return arch->getCache(i);
}


void InstructionSimulation::mainMemoryRead()
{
	time += 500; // todo: actual main read time
}

void InstructionSimulation::reportEvent(string e)
{
	std::cout << "event: " + e << ". during simulate of addr: " << add->getAddr() << std::endl;
	// note variables encapsulated in InstructionSimulation instance:
	// vector<CacheEvent> events
	// todo: events.push(new CacheEvent)
}
