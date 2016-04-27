#include "CacheSimulator.h"
#include "InstructionSimulation.h"
#include "InstructionSimulationRead.h"
#include "InstructionSimulationWrite.h"
#include "InstructionSimulationReadInstruction.h"
#include "CacheUpdater.h"
#include "CacheSearch.h"
#include "json.hpp"

#include <iostream>
#include <fstream>

#define READ 0
#define WRITE 1
#define INSTRUCTION 2

using json = nlohmann::json;

CacheSimulator::CacheSimulator()
{
	architecture = nullptr;
}

void CacheSimulator::createArchitecture(string jsonFilename)
{
	// read file at jsonFilename location and parse architecture
	ifstream confstream;
	json conf;
	std::vector<cacheParameters>  params;
	try
	{
		confstream.open(jsonFilename);
		confstream >> conf;
		confstream.close();

		int last_priority = -1;

		if (!conf.empty() && conf.find("caches") != conf.end())
		{

			params.resize(conf["caches"].size());

			for (int i = 0; i < conf["caches"].size(); i++)
			{
				std::array<std::string, 7> values = { 
					"name",
					"priority",
					"associativity",
					"block_size",
					"cache_size",
					"miss_time",
					"hit_time" 
				};

				for (int j = 0; j < 7; j++)
				{
					int this_priority = conf["caches"][i]["priority"];
					if (!conf["caches"][i][values[j]].is_number()
						&& !(conf["caches"][i][values[j]].is_string() && j == 0)
						&& last_priority < this_priority)
					{
						cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
						return;
					}
					last_priority++;
				}

				params[i] = cacheParameters();
				params[i].priority = conf["caches"][i]["priority"].get<int>();
				params[i].blockSize = conf["caches"][i]["block_size"].get<int>();
				params[i].name = conf["caches"][i]["name"].get<string>();
				params[i].size = conf["caches"][i]["cache_size"].get<int>();
				params[i].associativity = conf["caches"][i]["associativity"].get<int>();
				params[i].missPenalty = conf["caches"][i]["miss_time"].get<int>();
				params[i].hitTime = conf["caches"][i]["hit_time"].get<int>();

				// todo: parse replacment policy ( 0 = random, 1 = LRU)
				// todo: parse "use instruction cache" (boolean)
				params[i].replacementPolicy = cacheParameters::ReplacementPolicy::RANDOM;

			}
		}
		else
		{
			cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
			return;
		}

	}
	catch (exception& e)
	{
		cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
		return;
	}

	if (architecture != nullptr) {
		delete architecture;
	}

	// pass parsed params into simulator's cacheArchitecture instance
	architecture = new cacheArchitecture(params[0]);
	for (int i = 1; i < params.size(); i++)
		architecture->addCache(params[i]);


	// todo: check boolean in config: useInstructionCache?

	cacheParameters instr = params[0]; // instruction cache is clone of L1
	architecture->useInstructionCache(instr);
}

void CacheSimulator::readTrace(std::istream& source)
{
	unsigned int action;
	unsigned int addr;
	unsigned long long time = 0;

	CacheSearch *finder = new CacheSearch();

	for (string line; getline(source, line);)
	{
		// getline followed by scanf causes only every other line in input to be read
		//scanf_s("%u %x", &action, &addr);

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

		inst->simulate(finder, architecture, addrInstance);
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
