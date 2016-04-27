#pragma once
#include "InstructionSimulation.h"
class InstructionSimulationReadInstruction : public InstructionSimulation {
	void InstructionSimulationReadInstruction::hitCache(cache * cache);
	void InstructionSimulationReadInstruction::missCache(cache * cache);
	void InstructionSimulationReadInstruction::writeForward(cache * cache);

	/**
	 * Instruction Reads will return the instruction cache when 
	 * appropriate
	 */
	cache * getCacheAtIndex(int i);
};