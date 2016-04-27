#pragma once
#include "InstructionSimulationWrite.h"

void InstructionSimulationWrite::hitCache(cache * cache)
{
	reportEvent("write hit");
	time += cache->getHitTime();
}
void InstructionSimulationWrite::missCache(cache * cache)
{
	reportEvent("write miss");
	time += cache->getMissPenalty();
}
void InstructionSimulationWrite::writeForward(cache * cache)
{
	reportEvent("write write forward");
	updater->writeToCache(cache, add);
}

