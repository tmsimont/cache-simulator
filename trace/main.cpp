#include "CacheTest.h"
#include "CacheSimulator.h"
#include <iostream>


int main(int argc, char**argv)
{

	if (argc < 2) {
		std::cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
		return -1;
	}

	CacheSimulator sim = CacheSimulator();
	sim.createArchitecture(argv[1]);
	sim.readTrace(std::cin);

	return 0;
}