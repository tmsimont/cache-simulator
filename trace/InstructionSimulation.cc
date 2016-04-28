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

	// CacheUpdater holds a reference to a unique target cache
	// This is tightly coupled with a cache instance.
	// This is used here to make passing arguments a little bit
	// cleaner from simulation to instruction to extended instructions
	CacheUpdater* updater;


	// -----------------------------------------------------------------
	// MAIN LOOP: search L1 out to LN caches
	// -----------------------------------------------------------------
	while ((i < arch->getNumbCaches()) && (!found))
	{
		// set this instruction instance's currentCache pointer
		updater = getCacheUpdaterAtIndex(i);
		currentCache = updater->getCache();

		// search the cache
		finder->search(currentCache, add);
		found = finder->wasFound();

		if (found)
		{

			// --------------------------------------------------------
			// L(i) CACHE HIT
			// --------------------------------------------------------

			// let extensible instruction instance handle hit with updater
			hitCache(updater); // updater is tied to the cache being hit

			// write forward from L(i) ... L1
			for (int j = i - 1; j >= 0; --j)
			{
				previousCache = currentCache;
				updater = getCacheUpdaterAtIndex(j);
				currentCache = updater->getCache();

				// let extensible instruction instance handle write with updater
				writeForward(updater); // updater is tied to the cache being written
				checkForWriteBack(updater);

				if (updater->evictedDirtyBlock()) {
					mainMemoryRead();
				}
			}
		}
		else
		{

			// --------------------------------------------------------
			// L(i) CACHE MISS
			// --------------------------------------------------------

			// let extensible instruction instance handle miss with updater
			missCache(updater); // updater is tied to the cache being missed
		}
		++i;
	}


	// --------------------------------------------------------
	// L1 to LN all CACHE MISS
	// no caches have the address
	// --------------------------------------------------------
	if (!found)
	{
		mainMemoryRead();
		previousCache = nullptr;

		// write forward from main memory to LN ... L1
		for (int j = arch->getNumbCaches() - 1; j >= 0; --j)
		{
			// track the previousCache (for event recording) if previous is not main memory
			if (j < arch->getNumbCaches() - 1) {
				CacheUpdater * previousUpdater = getCacheUpdaterAtIndex(j + 1);
				previousCache = previousUpdater->getCache();
			}
			updater = getCacheUpdaterAtIndex(j);
			currentCache = updater->getCache();

			// let extensible instruction instance handle write with updater
			writeForward(updater); // updater is tied to the cache being written
			checkForWriteBack(updater);
		}
	}

	return events;
}

void InstructionSimulation::checkForWriteBack(CacheUpdater * updater)
{
	if (arch->writePolicy == cacheParameters::writePolicy::BACK && updater->evictedDirtyBlock()) {
		// write through to other caches L(i) to LN to Main Memory
		for (int j = updater->getCache()->getPriority() + 1; j < arch->getNumbCaches(); ++j) {
			CacheUpdater *otherCacheUpdater = getCacheUpdaterAtIndex(j);
			// todo: use CacheUpdater on other cache to write through
		}

		// write to main memory
		mainMemoryRead();
	}
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
	// finder->setWhereFound()
	// finder->blockWhereFound()
	// vector<CacheEvent> events
	// @todo: events.push(new CacheEvent)
}
