#pragma once
#include "InstructionSimulationWrite.h"

void InstructionSimulationWrite::hitCache(cache * cache)
{
	time += cache->getHitTime();
}
void InstructionSimulationWrite::missCache(cache * cache)
{
	time += cache->getMissPenalty();
}
void InstructionSimulationWrite::writeForward(cache * cache)
{
	cache->write(*add);
}

