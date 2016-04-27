#include "CacheTest.h"
#include "CacheSimulator.h"
#include <iostream>

int main(int argc, char**argv)
{

	CacheSimulator sim = CacheSimulator();
	sim.createArchitecture("filname.json");
	sim.readTrace(std::cin);


}