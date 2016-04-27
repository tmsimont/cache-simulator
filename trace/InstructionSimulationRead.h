#ifndef INSTRUCTIONSIMULATIONREAD_H
#define INSTRUCTIONSIMULATIONREAD_H
#include "InstructionSimulation.h"
class InstructionSimulationRead : public InstructionSimulation {
	void InstructionSimulationRead::hitCache(cache * cache);
	void InstructionSimulationRead::missCache(cache * cache);
	void InstructionSimulationRead::writeForward(cache * cache);
};

#endif // INSTRUCTIONSIMULATIONREAD_H