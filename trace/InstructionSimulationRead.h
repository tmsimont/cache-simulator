#ifndef INSTRUCTIONSIMULATIONREAD_H
#define INSTRUCTIONSIMULATIONREAD_H
#include "InstructionSimulation.h"
class InstructionSimulationRead : public InstructionSimulation {
	void InstructionSimulationRead::hitCache(CacheUpdater * updater);
	void InstructionSimulationRead::missCache(CacheUpdater * updater);
	void InstructionSimulationRead::writeForward(CacheUpdater * updater);
};

#endif // INSTRUCTIONSIMULATIONREAD_H