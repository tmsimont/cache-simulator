#include "InstructionSimulationWrite.h"

void InstructionSimulationWrite::hitCache(CacheUpdater * updater)
{
	reportEvent("write hit");
	updater->hitCache(add, finder->setWhereFound(), finder->blockWhereFound());
	time += updater->getCache()->getHitTime();

	// todo: check arch write policy and 
	if (arch->writePolicy == cacheParameters::writePolicy::BACK) {
		// todo: set invalid bit
		// can use finder->blockWhereFound() and finder->setWhereFound()
	}
	else if (arch->writePolicy == cacheParameters::writePolicy::THROUGH) {
		// write through to other caches L(i) to LN to Main Memory
		for (int j = updater->getCache()->getPriority() + 1; j < arch->getNumbCaches(); ++j) {
			CacheUpdater *otherCacheUpdater = getCacheUpdaterAtIndex(j);
			// todo: use CacheUpdater on for
		}
	}
}
void InstructionSimulationWrite::missCache(CacheUpdater * updater)
{
	reportEvent("write miss");
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationWrite::writeForward(CacheUpdater * updater)
{
	reportEvent("write write forward");
	updater->writeToCache(arch->writePolicy, add);
}

