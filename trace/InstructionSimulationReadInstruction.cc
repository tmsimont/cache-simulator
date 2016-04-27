#pragma once
#include "InstructionSimulationReadInstruction.h"

void InstructionSimulationReadInstruction::hitCache(cache * cache)
{
	reportEvent("instr hit");
	time += cache->getHitTime();
}
void InstructionSimulationReadInstruction::missCache(cache * cache)
{
	reportEvent("instr miss");
	time += cache->getMissPenalty();
}
void InstructionSimulationReadInstruction::writeForward(cache * cache)
{
	reportEvent("instr write forward");
	updater->writeToCache(cache, add);
}

cache* InstructionSimulationReadInstruction::getCacheAtIndex(int i) {
	if (i == 0)
		return arch->getInstructionCache();
	else
		return arch->getCache(i);
}