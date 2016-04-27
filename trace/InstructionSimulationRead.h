#ifndef INSTRUCTIONSIMULATIONREAD_H
#define INSTRUCTIONSIMULATIONREAD_H
#include "InstructionSimulation.h"
class InstructionSimulationRead : public InstructionSimulation {
	void hitCache(CacheUpdater * updater);
	void missCache(CacheUpdater * updater);
	void writeForward(CacheUpdater * updater);
};

#endif // INSTRUCTIONSIMULATIONREAD_H
