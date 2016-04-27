#pragma once
#include "InstructionSimulation.h"
class InstructionSimulationWrite : public InstructionSimulation {
	void InstructionSimulationWrite::hitCache(cache * cache);
	void InstructionSimulationWrite::missCache(cache * cache);
	void InstructionSimulationWrite::writeForward(cache * cache);
};
