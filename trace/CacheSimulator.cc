#include "CacheSimulator.h"
#include "InstructionSimulation.h"
#include "InstructionSimulationRead.h"
#include "InstructionSimulationWrite.h"
#include "InstructionSimulationReadInstruction.h"
#include "CacheUpdater.h"
#include "CacheSearch.h"
#include "ConfigParse.h"

#include <iostream>
#include <fstream>

#define READ 0
#define WRITE 1
#define INSTRUCTION 2


CacheSimulator::CacheSimulator()
{
	architecture = nullptr;
}

void CacheSimulator::createArchitecture(string inputfile)
{
	// read file at jsonFilename location and parse architecture
	ConfigParse parser = ConfigParse(inputfile);
	std::vector<cacheParameters> params = parser.getParams();

	// delete any previously existing architecture object
	if (architecture != nullptr) {
		delete architecture;
	}

	// pass parsed params into simulator's cacheArchitecture instance
	architecture = new cacheArchitecture(params[0]);
	for (int i = 1; i < params.size(); i++)
		architecture->addCache(params[i]);


	// check boolean in config: instructionCache
	if (parser.hasInstructionCache()) {
		cacheParameters instr = params[0]; // instruction cache is clone of L1
		architecture->useInstructionCache(instr);
	}

	if (parser.verboseOutput())
	{
		verboseOutput = true;
	}

}

void CacheSimulator::readTrace(std::istream& source)
{
	unsigned int action;
	unsigned int addr;
	unsigned long long time = 0;

	CacheSearch *finder = new CacheSearch();

	for (string line; getline(source, line);)
	{
		sscanf_s(line.c_str(), "%u %x", &action, &addr);

		InstructionSimulation *inst;
		address *addrInstance = new address(addr);
		if (action == READ)
		{
			inst = new InstructionSimulationRead();
		}
		else if (action == WRITE)
		{
			inst = new InstructionSimulationWrite();
		}
		else if (action == INSTRUCTION)
		{
			inst = new InstructionSimulationReadInstruction();
		}
		else {
			delete addrInstance;
			continue;
		}

		inst->simulate(finder, architecture, addrInstance, verboseOutput);
		time += inst->getTime();

		// trash memory we're done
		delete inst;
		delete addrInstance;
	}

	delete finder;

}

CacheSimulator::~CacheSimulator()
{
	if (architecture != nullptr) {
		delete architecture;
	}
}
