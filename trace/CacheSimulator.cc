#include "CacheSimulator.h"
#include "InstructionSimulation.h"
#include "InstructionSimulationRead.h"
#include "InstructionSimulationWrite.h"
#include "InstructionSimulationReadInstruction.h"
#include "CacheUpdater.h"
#include "CacheSearch.h"
#include "ConfigParse.h"
#include "CacheStatistics.h"

#include <iostream>
#include <fstream>

#define READ 0
#define WRITE 1
#define INSTRUCTION 2


CacheSimulator::CacheSimulator()
{
	architecture = nullptr;
	statistics = nullptr;
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

	// delete any previously existing statistics object
	if (statistics != nullptr) {
		delete statistics;
	}

	// pass parsed params into simulator's cacheArchitecture instance
	statistics = new cacheStatistics(architecture->getNumbCaches());

}

void CacheSimulator::readTrace(std::istream& source)
{
	unsigned int action;
	unsigned int addr;
	unsigned long long time = 0;

	CacheSearch *finder = new CacheSearch();

	for (string line; getline(source, line);)
	{
		sscanf(line.c_str(), "%u %x", &action, &addr);

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
		inst->setStatistics(statistics);
		inst->simulate(finder, architecture, addrInstance, verboseOutput);
		time += inst->getTime();
		statistics->incrementTime(inst->getTime());

		// trash memory we're done
		delete inst;
		delete addrInstance;
	}

	delete finder;

}

void CacheSimulator::output() {
	statistics->display();
}

CacheSimulator::~CacheSimulator()
{
	if (architecture != nullptr) {
		delete architecture;
	}
	if (statistics != nullptr) {
		delete statistics;
	}
}
