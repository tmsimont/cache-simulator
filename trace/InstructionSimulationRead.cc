#pragma once
#include "InstructionSimulationRead.h"

void InstructionSimulationRead::hitCache(cache * cache)
{
	time += cache->getHitTime();
}
void InstructionSimulationRead::missCache(cache * cache)
{
	time += cache->getMissPenalty();
}
void InstructionSimulationRead::writeForward(cache * cache)
{
	cache->write(*add);
}
