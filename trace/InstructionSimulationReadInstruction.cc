#pragma once
#include "InstructionSimulationReadInstruction.h"

void InstructionSimulationReadInstruction::hitCache(cache * cache)
{
	time += cache->getHitTime();
}
void InstructionSimulationReadInstruction::missCache(cache * cache)
{
	time += cache->getMissPenalty();
}
void InstructionSimulationReadInstruction::writeForward(cache * cache)
{
	cache->write(*add);
}

cache* InstructionSimulationReadInstruction::getCacheAtIndex(int i) {
	if (i == 0)
		return arch->getInstructionCache();
	else
		return arch->getCache(i);
}