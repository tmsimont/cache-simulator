#include "InstructionSimulationReadInstruction.h"

void InstructionSimulationReadInstruction::hitCache(CacheUpdater * updater)
{
	reportEvent("instr hit");
	updater->hitCache(add, finder->setWhereFound(), finder->blockWhereFound());
	time += updater->getCache()->getHitTime();
}
void InstructionSimulationReadInstruction::missCache(CacheUpdater * updater)
{
	reportEvent("instr miss");
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationReadInstruction::writeForward(CacheUpdater * updater)
{
	reportEvent("instr write forward");
	// todo: there is a vector of events passed back from write to cache.. 
	// append events to this->events
	// todo: get time of write
	updater->writeToCache(arch->writePolicy, add);
}

CacheUpdater* InstructionSimulationReadInstruction::getCacheUpdaterAtIndex(int i) {
	if (i == 0)
		return arch->getInstructionCacheUpdater();
	else
		return arch->getCacheUpdater(i);
}
