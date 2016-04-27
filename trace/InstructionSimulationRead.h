#pragma once
#include "InstructionSimulation.h"
class InstructionSimulationRead : public InstructionSimulation {
	void InstructionSimulationRead::hitCache(cache * cache);
	void InstructionSimulationRead::missCache(cache * cache);
	void InstructionSimulationRead::writeForward(cache * cache);
};
