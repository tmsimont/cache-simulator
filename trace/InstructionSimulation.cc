#pragma once
#include "InstructionSimulation.h"
#include <iostream>

vector<CacheEvent> InstructionSimulation::simulate(cacheArchitecture* arch, address* add)
{
	this->arch = arch;
	this->add = add;
	this->previousCache = nullptr;
	this->currentCache = nullptr;
	this->events = vector<CacheEvent>();
	this->time = 0;

	int i = 0;
	bool found = false;
	CacheSearch finder = CacheSearch();

	// search L1 out to LN caches
	while ((i < arch->getNumbCaches()) && (!found))
	{
		// set this instruction instance's currentCache pointer
		currentCache = getCacheAtIndex(i);

		// search the cache
		found = finder.cacheHasAddress(*currentCache, *add);

		if (found)
		{
			hitCache(currentCache);

			// write forward from L(i) ... L1
			for (int j = i - 1; j >= 0; --j)
			{
				previousCache = currentCache;
				currentCache = getCacheAtIndex(i);
				writeForward(currentCache);
			}
		}
		else
		{
			missCache(currentCache);
		}
		++i;
	}

	// no caches have the address
	if (!found)
	{
		mainMemoryRead();
		previousCache = nullptr;

		// write forward from main memory to LN ... L1
		for (int j = arch->getNumbCaches() - 1; j >= 0; --j)
		{
			if (j < arch->getNumbCaches() - 2) {
				previousCache = getCacheAtIndex(j + 1);
			}
			currentCache = getCacheAtIndex(j);
			writeForward(currentCache);
		}
	}

	return events;
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
	// note variables encapsulated in InstructionSimulation instance (see InstructionSimulation.h)
	// time
	// previousCache (might be nullptr if coming form main memory)
	// currentCache
	// vector<CacheEvent> events
	// @todo: events.push(new CacheEvent)
}
