#pragma once
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
	updater->writeToCache(add);
}

CacheUpdater* InstructionSimulationReadInstruction::getCacheUpdaterAtIndex(int i) {
	if (i == 0)
		return arch->getInstructionCacheUpdater();
	else
		return arch->getCacheUpdater(i);
}