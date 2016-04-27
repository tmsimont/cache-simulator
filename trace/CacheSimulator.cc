#include "CacheSimulator.h"
#include "InstructionSimulation.h"
#include "InstructionSimulationRead.h"
#include "InstructionSimulationWrite.h"
#include "InstructionSimulationReadInstruction.h"

#define READ 0
#define WRITE 1
#define INSTRUCTION 2

CacheSimulator::CacheSimulator()
{
}

void CacheSimulator::createArchitecture(string jsonFilename)
{
	// todo: read file at jsonFilename location and parse architecture
	cacheParameters d1 = cacheParameters(0, 64, "dL1", 1024, 2, 5, 1);
	cacheParameters d2 = cacheParameters(1, 64, "dL2", 8 * 64 * 1024, 4, 10, 6);
	cacheParameters d3 = cacheParameters(2, 64, "dL3", 8 * 1024 * 1024, 1, 15, 11);

	architecture = cacheArchitecture(d1);
	architecture.addCache(d2);
	//data.addCache(d3);
	cacheParameters instr = cacheParameters(0, 64, "iL1", 1024, 2, 5, 1);
	architecture.useInstructionCache(instr);
}

void CacheSimulator::readTrace(std::istream& source)
{
	unsigned int action;
	unsigned int addr;
	unsigned long long time = 0;

	for (string line; getline(source, line);)
	{
		scanf_s("%u %x", &action, &addr);


		if (action == READ)
		{
			time += architecture.cacheRead(address(addr));
		}
		else if (action == WRITE)
		{
			time += architecture.cacheWrite(address(addr));
		}
		else if (action == INSTRUCTION)
		{
			time += architecture.instructionRead(address(addr));
		}
	}

}
