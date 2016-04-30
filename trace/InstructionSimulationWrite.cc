#include "InstructionSimulationWrite.h"

void InstructionSimulationWrite::hitCache(CacheUpdater * updater)
{
	reportEvent("write hit");
	statistics->incrementCacheWriteHits(currentCache->getPriority());
	updater->hitCache(add, finder->setWhereFound(), finder->blockWhereFound());
	time += updater->getCache()->getHitTime();

	if (arch->writePolicy == cacheParameters::WritePolicy::BACK) {
		// todo: set invalid bit
		//TODO in future: fully implement write-back in addition to write-through
		// can use finder->blockWhereFound() and finder->setWhereFound()
	}
	else if (arch->writePolicy == cacheParameters::WritePolicy::THROUGH) {
		// write through to other caches L(i) to LN to Main Memory
		for (int j = updater->getCache()->getPriority() + 1; j < arch->getNumbCaches(); ++j) {
			CacheUpdater *otherCacheUpdater = getCacheUpdaterAtIndex(j);
			reportEvent("write through to " + otherCacheUpdater->getCache()->getName());
			otherCacheUpdater->writeToCache(this->add);
			
		}
	}
}
void InstructionSimulationWrite::missCache(CacheUpdater * updater)
{
	reportEvent("write miss");
	statistics->incrementCacheWriteMisses(currentCache->getPriority());
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationWrite::writeForward(CacheUpdater * updater)
{
	reportEvent("write write forward");

	// todo: there is a vector of events passed back from write to cache.. 
	// append events to this->events
	// todo: get time of write
	updater->writeToCache(add);
}

