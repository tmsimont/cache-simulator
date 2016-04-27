#ifndef INSTRUCTIONSIMULATIONWRITE_H
#define INSTRUCTIONSIMULATIONWRITE_H
#include "InstructionSimulation.h"
class InstructionSimulationWrite : public InstructionSimulation {
	void hitCache(CacheUpdater * updater);
	void missCache(CacheUpdater * updater);
	void writeForward(CacheUpdater * updater);
};
#endif // INSTRUCTIONSIMULATIONWRITE_H
