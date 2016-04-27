#include "CacheSimulator.h"
#include "InstructionSimulation.h"
#include "InstructionSimulationRead.h"
#include "InstructionSimulationWrite.h"
#include "InstructionSimulationReadInstruction.h"
//#include "json.hpp"

#include <iostream>
#include <fstream>

#define READ 0
#define WRITE 1
#define INSTRUCTION 2

//using json = nlohmann::json;

CacheSimulator::CacheSimulator()
{
}

/*
void CacheSimulator::createArchitecture(string jsonFilename)
{
	// todo: read file at jsonFilename location and parse architecture


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
				std::array<std::string, 7> values = { "name","priority","associativity", "block_size","cache_size","miss_time","hit_time" };

				for (int j = 0; j < 7; j++)
				{
					int this_priority = conf["caches"][i]["priority"];
					if (!conf["caches"][i][values[j]].is_number() && !(conf["caches"][i][values[j]].is_string() && j == 0) && last_priority < this_priority )
					{
						cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
						return;
					}
					last_priority++;
				}

				params[i] = cacheParameters(conf["caches"][i]["priority"], conf["caches"][i]["block_size"], conf["caches"][i]["name"], conf["caches"][i]["cache_size"], conf["caches"][i]["associativity"], conf["caches"][i]["miss_time"], conf["caches"][i]["hit_time"]);

			}
		}
		else
		{
			return;
		}

	}
	catch (exception& e)
	{
		cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
	}


	architecture = cacheArchitecture(params[0]);

	for (int i = 1; i < params.size(); i++)
		architecture.addCache(params[i]);
	
	cacheParameters instr = cacheParameters(conf["caches"][0]["priority"], conf["caches"][0]["block_size"], conf["caches"][0]["name"], conf["caches"][0]["cache_size"], conf["caches"][0]["associativity"], conf["caches"][0]["miss_time"], conf["caches"][0]["hit_time"]);
	architecture.useInstructionCache(instr);
}

*/
void CacheSimulator::createArchitectureTest()
{
	cacheParameters d1 = cacheParameters(0, 64, "dL1", 1024, 2, 5, 1);
	cacheParameters d2 = cacheParameters(1, 64, "dL2", 8 * 64 * 1024, 4, 10, 6);
	architecture = cacheArchitecture(d1);
	architecture.addCache(d2);
	architecture.useInstructionCache(d1);
}

void CacheSimulator::readTrace(std::istream& source)
{
	unsigned int action;
	unsigned int addr;
	unsigned long long time = 0;

	for (string line; getline(source, line);)
	{
		scanf_s("%u %x", &action, &addr);

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

		inst->simulate(&architecture, addrInstance);

		// trash memory we're done
		delete inst;
		delete addrInstance;
	}

}
