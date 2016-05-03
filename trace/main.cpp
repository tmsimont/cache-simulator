#include "CacheTest.h"
#include "CacheSimulator.h"
#include <iostream>


int main(int argc, char**argv)
{

	if (argc < 2) {
		std::cout << "usage: [executable] [configuration file] < [input file] > [output file]" << endl;
		return -1;
	}

  std::string outConfigID = "";
  std::string outTraceFile = "-";
  outConfigID = argv[1];
  if (argc == 3)
    outTraceFile = argv[2];

	CacheSimulator sim = CacheSimulator();
	sim.createArchitecture(argv[1]);
	sim.readTrace(std::cin);
	sim.output(outConfigID, outTraceFile);

	return 0;
}
