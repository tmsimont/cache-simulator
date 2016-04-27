#include "InstructionSimulationRead.h"

void InstructionSimulationRead::hitCache(CacheUpdater * updater)
{
	reportEvent("read hit");
	updater->hitCache(add, finder->setWhereFound(), finder->blockWhereFound());
	time += updater->getCache()->getHitTime();
}
void InstructionSimulationRead::missCache(CacheUpdater * updater)
{
	reportEvent("read miss");
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationRead::writeForward(CacheUpdater * updater)
{
	reportEvent("read write forward");
	updater->writeToCache(add);
}
