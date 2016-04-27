#include "CacheTest.h"
#include "CacheSimulator.h"
#include <iostream>

int main(int argc, char**argv)
{

	CacheSimulator sim = CacheSimulator();
	sim.createArchitecture(argv[1]);
	sim.readTrace(std::cin);


}