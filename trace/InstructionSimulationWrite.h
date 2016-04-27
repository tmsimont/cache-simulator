#ifndef INSTRUCTIONSIMULATIONWRITE_H
#define INSTRUCTIONSIMULATIONWRITE_H
#include "InstructionSimulation.h"
class InstructionSimulationWrite : public InstructionSimulation {
	void InstructionSimulationWrite::hitCache(cache * cache);
	void InstructionSimulationWrite::missCache(cache * cache);
	void InstructionSimulationWrite::writeForward(cache * cache);
};
#endif // INSTRUCTIONSIMULATIONWRITE_H