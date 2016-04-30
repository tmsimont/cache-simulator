#ifndef CACHESIMULATOR_H
#define CACHESIMULATOR_H
#include "CacheArchitecture.h"
#include "CacheParameters.h"
#include <iostream>
#include <string>
class CacheSimulator
{
public:
	CacheSimulator();
	void createArchitecture(string inputfile);
	void readTrace(std::istream& source);
	~CacheSimulator();
private:
	cacheArchitecture * architecture;
	bool verboseOutput = false;
};

#endif // CACHESIMULATOR_H
