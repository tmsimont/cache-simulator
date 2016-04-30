#include "InstructionSimulationRead.h"

void InstructionSimulationRead::hitCache(CacheUpdater * updater)
{
	reportEvent("read hit");
	updater->hitCache(add, finder->setWhereFound(), finder->blockWhereFound());
	statistics->incrementCacheReadHits(currentCache->getPriority());
	time += updater->getCache()->getHitTime();
}
void InstructionSimulationRead::missCache(CacheUpdater * updater)
{
	reportEvent("read miss");
	statistics->incrementCacheReadMisses(currentCache->getPriority());
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationRead::writeForward(CacheUpdater * updater)
{
	reportEvent("read write forward");
	// todo: there is a vector of events passed back from write to cache.. 
	// append events to this->events
	// todo: get time of write
	updater->writeToCache(add);
}
