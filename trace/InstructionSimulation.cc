#pragma once
#include "InstructionSimulation.h"
#include <iostream>

vector<CacheEvent> InstructionSimulation::simulate(CacheSearch * finder, cacheArchitecture* arch, address* add)
{
	this->finder = finder;
	this->arch = arch;
	this->add = add;
	this->previousCache = nullptr;
	this->currentCache = nullptr;
	this->events = vector<CacheEvent>();
	this->time = 0;

	int i = 0;
	bool found = false;
	CacheUpdater* updater;

	// search L1 out to LN caches
	while ((i < arch->getNumbCaches()) && (!found))
	{
		// set this instruction instance's currentCache pointer
		updater = getCacheUpdaterAtIndex(i);
		currentCache = updater->getCache();

		// search the cache
		found = finder->cacheHasAddress(currentCache, add);

		if (found)
		{
			hitCache(updater);

			// write forward from L(i) ... L1
			for (int j = i - 1; j >= 0; --j)
			{
				previousCache = currentCache;
				updater = getCacheUpdaterAtIndex(j);
				currentCache = updater->getCache();
				writeForward(updater);
			}
		}
		else
		{
			missCache(updater);
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
			if (j < arch->getNumbCaches() - 1) {
				CacheUpdater * previousUpdater = getCacheUpdaterAtIndex(j + 1);
				previousCache = previousUpdater->getCache();
			}
			updater = getCacheUpdaterAtIndex(j);
			currentCache = updater->getCache();
			writeForward(updater);
		}
	}

	return events;
}

int InstructionSimulation::getTime()
{
	return time;
}


CacheUpdater* InstructionSimulation::getCacheUpdaterAtIndex(int i) {
	return arch->getCacheUpdater(i);
}


void InstructionSimulation::mainMemoryRead()
{
	time += 500; // todo: actual main read time
}

void InstructionSimulation::reportEvent(string e)
{
	std::cout << currentCache->getName() << " event: " + e << ". during simulate of addr: " << add->getAddr() << std::endl;
	// note variables encapsulated in InstructionSimulation instance (see InstructionSimulation.h)
	// time
	// previousCache (might be nullptr if coming form main memory)
	// currentCache
	// vector<CacheEvent> events
	// @todo: events.push(new CacheEvent)
}
