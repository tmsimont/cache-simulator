#pragma once
#include "InstructionSimulationRead.h"

void InstructionSimulationRead::hitCache(cache * cache)
{
	reportEvent("read hit");
	time += cache->getHitTime();
}
void InstructionSimulationRead::missCache(cache * cache)
{
	reportEvent("read miss");
	time += cache->getMissPenalty();
}
void InstructionSimulationRead::writeForward(cache * cache)
{
	reportEvent("read write forward");
	updater->writeToCache(cache, add);
}
