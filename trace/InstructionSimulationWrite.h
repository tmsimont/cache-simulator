#ifndef INSTRUCTIONSIMULATIONWRITE_H
#define INSTRUCTIONSIMULATIONWRITE_H
#include "InstructionSimulation.h"
class InstructionSimulationWrite : public InstructionSimulation {
	void InstructionSimulationWrite::hitCache(CacheUpdater * updater);
	void InstructionSimulationWrite::missCache(CacheUpdater * updater);
	void InstructionSimulationWrite::writeForward(CacheUpdater * updater);
};
#endif // INSTRUCTIONSIMULATIONWRITE_H