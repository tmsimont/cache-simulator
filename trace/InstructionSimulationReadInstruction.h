#ifndef INSTRUCTIONSIMULATIONREADINSTRUCTION_H
#define INSTRUCTIONSIMULATIONREADINSTRUCTION_H
#include "InstructionSimulation.h"
class InstructionSimulationReadInstruction : public InstructionSimulation {
	void InstructionSimulationReadInstruction::hitCache(CacheUpdater * updater);
	void InstructionSimulationReadInstruction::missCache(CacheUpdater * updater);
	void InstructionSimulationReadInstruction::writeForward(CacheUpdater * updater);

	/**
	 * Instruction Reads will return the instruction cache updater when 
	 * appropriate
	 */
	CacheUpdater* getCacheUpdaterAtIndex(int i);
};

#endif // INSTRUCTIONSIMULATIONREADINSTRUCTION_H