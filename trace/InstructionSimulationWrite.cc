#pragma once
#include "InstructionSimulationWrite.h"

void InstructionSimulationWrite::hitCache(CacheUpdater * updater)
{
	reportEvent("write hit");
	time += updater->getCache()->getHitTime();
}
void InstructionSimulationWrite::missCache(CacheUpdater * updater)
{
	reportEvent("write miss");
	time += updater->getCache()->getMissPenalty();
}
void InstructionSimulationWrite::writeForward(CacheUpdater * updater)
{
	reportEvent("write write forward");
	updater->writeToCache(add);
}

